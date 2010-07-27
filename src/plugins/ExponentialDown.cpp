/********************************************************************************
This file is working code for a class which implements the exponential down model
for energy transfer during a collision, but it is heavily commented so as to be a
tutorial on the writing of classes which implement different energy transfer
models, or, more widely, models for other parts of the calculation. The parent
class in EnergyTransferModel.h is also commented.

These classes are plugin classes - they can be added or removed without having to
change any of the existing code. They derived from a base class (here it is
EnergyTransferModel) which is usually abstract. It has virtual functions which
are called by the main code and are probably redefined in the derived classes
like this one.

A plugin class can be declared in a .h file and defined in a .cpp file, as normal.
But the header file is unlikely ever to be used independently, so it may be
convenient for the declaration to be also in the .cpp file, so that the plugin is
all in one file, as here.
********************************************************************************/

#include "../EnergyTransferModel.h"
#include "../Rdouble.h"
#include "../MolecularComponents.h"
#include "../Molecule.h"
#include <cmath>

using namespace std ;

namespace mesmer
{
class ExponentialDown : public EnergyTransferModel
{
public:

/********************************************************************************
  Constructor which registers this class with the map of energy transfer models
  kept by the base class.
********************************************************************************/
  ExponentialDown(const std::string& id) : EnergyTransferModel(id),
    m_deltaEdown(0.0), m_refTemp(298), m_dEdExp(0.0) {}

  /******************************************************************************
  Because the class can be used for more than one molecule, a new instance is made
  for each one. This is done by EnergyTransferModel::Find() calling Clone(); a
  function of the following form is required for each derived class.
  ******************************************************************************/
  ExponentialDown* Clone() { return new ExponentialDown(*this); }

  /*************************************************************
  Read the parameters needed by the class from the XML datafile
  *************************************************************/
  virtual bool ReadParameters(const Molecule* parent) ; 

  /*************************************************************
  This is the function which does the real work of the plugin
  *************************************************************/
  virtual double calculateTransitionProbability(double Ei, double Ej);

private:
  Rdouble m_deltaEdown ;
  double m_refTemp;
  double m_dEdExp ;

};

  /******************************************************************************
  Declaration of a global instance of the class. This makes the class known to
  Mesmer and also defines its id "ExponentialDown".
  ******************************************************************************/
  ExponentialDown exponentialDown("ExponentialDown");

  /******************************************************************************
  The energy transfer model for each modelled molecule is specified in the XML
  datafile by a child element of <molecule>:
  <me:energyTransferModel>ExponentialDown</me:energyTransferModel>
  If this is omitted, the default method specified in defaults.xml is used (which
  is currently "ExponentialDown", but could be changed).
  ******************************************************************************/

  /******************************************************************************
  Plugin classes usually read the data they require from the XML datafile and may
  store it themselves, although less specialised data may be stored in Molecule
  or Reaction.
  ******************************************************************************/
  bool ExponentialDown::ReadParameters(const Molecule* parent) { 

    setParent(parent);
    PersistPtr pp = parent->get_PersistentPointer();
    PersistPtr ppProp = pp->XmlMoveToProperty("me:deltaEDown");

    /******************************************************************************
    The following statement reads the value of the CML property "me:deltaEDown". If
    it is not present the default value from defaults.xml is added to the internal
    XML tree and the value returned. This mechanism, which applies for most XmlRead
    operations unless there is a 'optional' parameter, is the recommended way to
    handle default values. It allows the default to be changed by the user, logs the
    use of the default, and provides error messages, including optional exhortations
    for the user to check the default (see the manual).
    ******************************************************************************/
    const char* txt = (parent->get_PersistentPointer())->XmlReadProperty("me:deltaEDown"); //required
    if(!txt)
      return false;
    istringstream idata(txt);
    double value(0.0);
    idata >> value;
    m_deltaEdown = value;

    /******************************************************************************
    m_deltaEdown behaves most of the time like a normal variable of type double.
    But it can be a "range variable", taking a range of values when used in grid
    search and fitting routines. The me:deltaEDown property having both "lower" and
    "upper" attributes, together with and the following code, sets this up.
    ******************************************************************************/
    double valueL   = ppProp->XmlReadDouble("lower", optional);
    double valueU   = ppProp->XmlReadDouble("upper", optional);
    double stepsize = ppProp->XmlReadDouble("stepsize" ,optional);
    if (valueL!=0.0 && valueU!=0.0){
      // make a range variable
      m_deltaEdown.set_range(valueL, valueU, stepsize, "deltaEdown");//incl parent in name?
      //Save PersistPtr of the XML source of this Rdouble
      RangeXmlPtrs.push_back(ppProp);
    }

    // The temperature dependence of <delta_E_down> is accounted for as:
    //
    // <delta_E_down>(T) = <delta_E_down>_ref * (T / refTemp)^dEdExp
    //
    // By default, dEdExp = 0, which means delta_E_down does not depend on temperature.
    // Reference temperature of <Delta E down>, refTemp, has default 298.

    m_refTemp = ppProp->XmlReadDouble("referenceTemperature", optional );
    if(m_refTemp==0.0)
      m_refTemp = 298.;

    m_dEdExp = ppProp->XmlReadDouble("exponent", optional); //defaults to 0.0

    return true ; 
  }
  /******************************************************************************
  This is the function which does the real work of the plugin
  ******************************************************************************/
  double ExponentialDown::calculateTransitionProbability(double Ei, double Ej) {
    // return exp(-(Ei -Ej)/m_deltaEdown) ;

    double deltaEDown = m_deltaEdown;
    if(m_dEdExp!=0.0) {
      const double temperature = 1.0/(boltzmann_RCpK * getParent()->getEnv().beta);
      deltaEDown = deltaEDown * pow((temperature/m_refTemp),m_dEdExp);
    }

    // issue a warning message and exit if delta_E_down is smaller than grain size.
    if (deltaEDown < double(getParent()->getEnv().GrainSize) && !getParent()->getFlags().allowSmallerDEDown)
      cerr << "Delta E down is smaller than grain size: the solution may not converge.";

    return exp(-(Ei -Ej)/deltaEDown) ;
  }

  /******************************************************************************
  In summary, to make a plugin class with a new energy transfer model:
    - Copy this file, changing all the "ExponentialDown" to your class name.
    - Change the code in calculateTransitionProbability() to your model.
    - Alter ReadParameters() to input any data your model needs from the XML file.
       Any data that is essential should preferably have an entry in defaults.xml,
       The "default" attribute of this should be in uppercase if it is necessary
       for the user to review the value of the default.
       If the data does not need to be provided, add an optional parameter to the
       call to an XmlRead function.
    - In the XML file, add or change
        <me:energyTransferModel>yourID</me:energyTransferModel>
        Add your data, which should usually have an me: prefix.
     
  ******************************************************************************/

}//namespace
