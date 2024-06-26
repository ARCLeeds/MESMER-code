#ifndef GUARD_DensityOfStates_h
#define GUARD_DensityOfStates_h

#include <map>
#include <string>
#include <vector>
#include "XMLPersist.h"
#include "plugin.h"

namespace mesmer
{
  class gDensityOfStates;
  struct MesmerEnv;

  // Abstract base class for cell Density Of States (DOS) calculators. The
  // derived concrete classes are plugin classes, so that new classes can be 
  // added without changing any of the existing code. The constructor of a global 
  // instance registers the class with the base class. Subsequently, supplying  
  // the id (a string) to the Find function returns a pointer to a new instance.

  class DensityOfStatesCalculator : public TopPlugin
  {
  public:
    DensityOfStatesCalculator() : m_thermoDynamicTable(), m_thermoContribTable(false), m_unitFctr(1.0) {}
    virtual ~DensityOfStatesCalculator() {}
    static const char* typeID() { return "Cell Density of States Calculators"; }
    virtual const char* getTypeID() { return typeID(); }
    virtual const char* typeDescription() {
      return
        "Normally it necessary to specify a density of states calculator that\n"
        "includes the rotations, such as ClassicalRotors, QMRotors or DefinedStates.\n"
        "In the XML datafile this is done like\n"
        "<me:DOSCMethod xsi:type=\"me:ClassicalRotors\"> or\n"
        "<me:DOSCMethod>QMRotors/> or <me:DOSCMethod name=\"QMRotors\"/>\n"
        "If no method is specified with <me:DOSCMethod>, the value from defaults.xml\n"
        "(currently ClassicalRotors) is used. The BeyerSwinehart method for vibrations\n"
        " is normally automatically included.\n"
        "Multiple additional methods can be specified like\n"
        "<me:ExtraDOSCMethod xsi:type=\"me:HinderedRotorQM1D\">\n"
        "  data for method...\n"
        "</me:ExtraDOSCMethod>\n";
    }
    virtual bool includesRotations() { return false; }

    //Get a pointer to a derived class by providing its id.
    static DensityOfStatesCalculator* Find(const std::string& id)
    {
      return dynamic_cast<DensityOfStatesCalculator*>(TopFind(id, typeID()));
    }

    // Return name.
    virtual std::string getName() = 0;

    // Read any data from XML and store in this instance. Default is do nothing.
    virtual bool ReadParameters(gDensityOfStates* gdos, PersistPtr ppDOSC = NULL) = 0;

    // Provide a function to define particular counts of the DOS of a molecule
    virtual bool countCellDOS(gDensityOfStates* mol, const MesmerEnv& env) = 0;

    // Provide a function to calculate contribution to canonical partition function.
    virtual void canPrtnFnCntrb(gDensityOfStates* gdos, double beta, double& PrtnFn, double& IntrlEne, double& varEne) = 0;

    // Provide a function to return the number of degrees of freedom associated with this count.
    virtual size_t NoDegOfFreedom(gDensityOfStates* gdos) = 0;

    // Provide a function to calculate the zero point energy of a molecule.
    virtual double ZeroPointEnergy(gDensityOfStates* gdos) { return 0.0; };

    // Initialize contributions to thermodynamic table.
    void InitThermoContrib(bool print, double unitFctr) {
      m_thermoContribTable = print;
      m_unitFctr = unitFctr;
    }

    // Finalize contributions to thermodynamic table.
    void FinalThermoContrib() {
      m_thermoContribTable = false;
      m_thermoDynamicTable = "";
    }

    // Write out table of contribution to thermodynamic functions.
    std::string ThermoDynamicWrite() const;

    // Method to create thermodymaic table header.
    void ThermoContribHeader(const std::string species, const std::string id, const std::string units);

  protected:

    // Method to add an entry to thermodymaic table header.
    void ThermoDynamicEntry(const double beta, const double CanPrtnFn, const double internalEnergy, const double varEnergy);

  private:

    std::string m_thermoDynamicTable;
    bool m_thermoContribTable;
    double m_unitFctr;

  };

}//namespace

#endif

