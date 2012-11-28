#ifndef GUARD_EnergyTransferModels_h
#define GUARD_EnergyTransferModels_h

//-------------------------------------------------------------------------------------------
//
// EnergyTransferModel.h
//
// Author: Struan Robertson
// Date:   27/Jun/2009
//
/*****************************************************************************
This header file contains the declaration of the EnergyTransferModel abstract
class. This class will be inherited by all energy transfer models.

The derived concrete classes are plugin classes- new classes can be added
without changing any of the existing code. ExponentialDown.cpp is a file
containing a derived class and has lots of comments.

The constructor of the derived classes register their presence and their IDs,
and this is passed to their grandparent class TopPlugin which maintains a list
of all plugins. Subsequently, supplying an id (a string) to the Find function of
the plugin type class (EnergyTransferModel here) provides a pointer to a new
instance. For historical reasons not all plugin classes have a Clone() function
to allow the use a new instance on every call to Find(), but it is worth
doing because it allows them to contain data pertaining to a particular molecule
or reaction.
*****************************************************************************/

#include <map>
#include <string>
#include "plugin.h"

namespace mesmer
{
// Forward declarations:
class Molecule;

class EnergyTransferModel : public TopPlugin
{
public:

  virtual ~EnergyTransferModel(){}

  virtual const char* getTypeID() override {return typeID();}

  /**********************************************************************
  Optional description which will appear in a verbose listing of plugins
  generated by the command line
     mesmer -T
  **********************************************************************/
  virtual const char* typeDescription() override { return
    "Classes for calculating energy transfer probabilities between grains\n"
    ;}

  /****************************************************************************
   EnergyTransferModel::Find() returns a pointer to a derived class from its id,
   or NULL if not recognized.
   In this class a new instance is returned, (a copy of a global instance)
   so that molecule-specific data can be stored in it. Some types of plugin use
   only the single global instance.
   It is the responsibility of the calling function to delete the instance.

   In this particular case the calling function is
   gWellProperties::initialization(). It parses the XML data file for a
   <me:energyTransferModel> element for each 'modelled' molecule. If not found
   the default id from defaults.xml is used, and this logged in the log file.
   EnergyTransferModel::Find(id) is called and then the derived class's
   ReadParameters(). The derived EnergyTransferModel class instance is deleted
   in the gWellProperties destructor.
  ****************************************************************************/
  static EnergyTransferModel* Find(const std::string& name)
  {
    return dynamic_cast<EnergyTransferModel*>(TopFind(name, typeID()));
  }

  /*************************************************************
  This is the function which does the real work of the plugin
  *************************************************************/
  virtual double calculateTransitionProbability(double Ei, double Ej) = 0 ;

  virtual bool ReadParameters(const Molecule* parent) = 0 ; 

  const Molecule* getParent() const {return m_parent;} ;
  void setParent(const Molecule* parent) { m_parent = parent;} ;

private:
  /*************************************************************
  The name for this plugin type that will appear in a listing of
  plugins, obtained by
     mesmer -t    or    mesmer -T  
  **************************************************************/
  static const char* typeID(){ return "Energy transfer models"; }
  const Molecule* m_parent;
};

}//namespace

#endif // GUARD_EnergyTransferModels_h
