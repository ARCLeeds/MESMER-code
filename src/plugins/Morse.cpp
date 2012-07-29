
//-------------------------------------------------------------------------------------------
//
// Morse.cpp
//
// Author: Struan Robertson
// Date:   08/Jul/2012
//
// This file contains the implementation of the methods for calculating and testing the 
// density of states of a set of decoupled morse oscilators.
//
//-------------------------------------------------------------------------------------------

#include "../DensityOfStates.h"
#include "../MolecularComponents.h"

using namespace std;
namespace mesmer
{
  class Morse : public DensityOfStatesCalculator
  {
  public:

    //Read data from XML. 
    virtual bool ReadParameters(gDensityOfStates* gdos, PersistPtr ppDOSC=NULL);

    // Function to define particular counts of the DOS of a molecule.
    virtual bool countCellDOS(gDensityOfStates* mol, size_t MaximumCell);

    // Function to calculate contribution to canonical partition function.
    virtual double canPrtnFnCntrb(gDensityOfStates* gdos, double beta) ;

    // Function to return the number of degrees of freedom associated with this count.
    virtual unsigned int NoDegOfFreedom(gDensityOfStates* gdos) ;

    ///Constructor which registers with the list of DensityOfStatesCalculators in the base class
    //This class calculates a complete DOS: it is not an extra class. 
    Morse(const std::string& id) : DensityOfStatesCalculator(id, true){}

    virtual ~Morse() {}
    virtual Morse* Clone() { return new Morse(*this); }

  private :

    PersistPtr m_ppDOSC ;
    vector<double> m_vibFreq ;  // The 0->1 transition of each Morse oscillator in cm-1.
    vector<double> m_anharmty ; // The associated anharmonicity.


  } ;

  //************************************************************
  //Global instance, defining its id (usually the only instance) but here with an alternative name
  Morse theMorse("Morse");
  //************************************************************

  //Read data from XML. 
  bool Morse::ReadParameters(gDensityOfStates* gdos, PersistPtr ppDOSC) {
    m_ppDOSC = ppDOSC ;
    PersistPtr pp = m_ppDOSC ;
    while(pp = pp->XmlMoveTo("me:MorseParameters")) {
      double vibFreq  = pp->XmlReadDouble("vibrationalFrequency", true);
      double anharmty = pp->XmlReadDouble("anharmoicity",         true);
      m_vibFreq.push_back(vibFreq) ;
      m_anharmty.push_back(-fabs(anharmty)) ; // Ensure the anharmonicity is negative.
    }

    return true ;
  }

  // Provide a function to define particular counts of the DOS of a molecule.
  bool Morse::countCellDOS(gDensityOfStates* pDOS, size_t MaximumCell)
  {
    vector<double> cellDOS;
    if(!pDOS->getCellDensityOfStates(cellDOS, 0, false)) // retrieve the DOS vector without recalculating
      return false;

    vector<double> tmpCellDOS(cellDOS) ;

    for (size_t nFrq(0) ; nFrq < m_vibFreq.size() ; nFrq++ )
    {
      double vibFreq  = m_vibFreq[nFrq];
      double anharmty = m_anharmty[nFrq];

      // Maximum bound energy.

      int nmax = int(-0.5*vibFreq/anharmty)  ;

      vector<double> energyLevels ;
      for (int n(0) ; n < nmax ; n++ ) {
        double nu = double(n) ;
        double energy = nu*vibFreq + nu*(nu + 1)*anharmty ;
        energyLevels.push_back(energy) ;
      }

      // Convolve with the density of states for the other degrees of freedom.

      for (size_t k(1) ; k < energyLevels.size() ; k++ ) {
        size_t nr = int(energyLevels[k]) ;
        if (nr < MaximumCell) {
          for (size_t i(0) ; i < MaximumCell - nr ; i++ ) {
            tmpCellDOS[i + nr] = tmpCellDOS[i + nr] + cellDOS[i] ;
          }
        }
      }
    }

    // Replace existing density of states.   

    pDOS->setCellDensityOfStates(tmpCellDOS) ;

    return true;
  }

  // Calculate contribution to canonical partition function.
  double Morse::canPrtnFnCntrb(gDensityOfStates* gdos, double beta) {

    double qtot(1.0) ; 
    for (size_t nFrq(0) ; nFrq < m_vibFreq.size() ; nFrq++ )
    {
      double vibFreq  = m_vibFreq[nFrq];
      double anharmty = m_anharmty[nFrq];

      // Maximum bound energy.

      int nmax = int(-0.5*vibFreq/anharmty)  ;

      double qtmp(0.0) ;
      for (int n(0) ; n < nmax ; n++ ) {
        double nu = double(n) ;
        double energy = nu*vibFreq + nu*(nu + 1)*anharmty ;
        qtmp = exp(-beta*energy) ;
      }

      qtot *= qtmp ;
    }

    return qtot ;
  }

  // Function to return the number of degrees of freedom associated with this count.
  unsigned int Morse::NoDegOfFreedom(gDensityOfStates* gdos) {
    return m_vibFreq.size() ;
  }

}//namespace
