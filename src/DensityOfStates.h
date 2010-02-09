#ifndef GUARD_DensityOfStates_h
#define GUARD_DensityOfStates_h

#include <map>
#include <string>
#include <vector>
#include "XMLPersist.h"

namespace mesmer
{
  class Molecule;
  class gDensityOfStates;

  /** Abstract base class for cell Density Of States (DOS) calculators for energy grained master equation (EGME).
  The derived concrete classes are plugin classes:
  -- New classes can be added without changing any of the existing code.
  They have a single global instance, the constructor of which registers
  the class with the base class. Subsequently, a pointer to the class is
  obtained by supplying the id (a string) to the Find function.
  **/
  class DensityOfStatesCalculator
  {
  public:
    typedef std::map<std::string, DensityOfStatesCalculator*> DensityOfStatesMap;

    ///Base class constructor adds the derived class instance to the map
    DensityOfStatesCalculator(const std::string& id, bool isExtra){ get_Map(isExtra)[id] = this; }

    virtual ~DensityOfStatesCalculator(){};
    virtual DensityOfStatesCalculator* Clone()=0;

    //Get a pointer to a derived class by providing its id.
    static DensityOfStatesCalculator* Find(const std::string& id, bool extraType=false)
    {
      DensityOfStatesMap::iterator pos = get_Map(extraType).find(id);
      if(pos==get_Map(extraType).end())
        return NULL; 
      return (pos->second)->Clone();
    }

    //Read any data from XML and store in this instance. Default is do nothing.
    virtual bool ReadParameters(Molecule* pMol, PersistPtr ppDOSC=NULL){ return true; };

    // provide a function to define particular counts of the DOS of a molecule
    virtual bool countCellDOS(gDensityOfStates* mol, int MaximumCell)=0;

  private:
    /// Returns a reference to the map of DensityOfStatesCalculator classes
    /// Is a function rather than a static member variable to avoid initialization problems.
    ///There are different maps for main (e.g. ClassicalRotors)and extra (e.g. HinderedRotorA) classes: 
    static DensityOfStatesMap& get_Map(bool extra)
    {
      static DensityOfStatesMap m;
      static DensityOfStatesMap mextra;
      return extra ? mextra : m;
    }

  };

}//namespace

#endif
