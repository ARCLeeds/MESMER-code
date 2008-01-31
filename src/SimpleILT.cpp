#include "SimpleILT.h"

using namespace std;
using namespace Constants;
namespace mesmer
{
  //************************************************************
  //Global instance, defining its id (usually the only instance)
  SimpleILT theSimpleILT("Simple ILT");
  //************************************************************

  //-----
  //short note for variables:
  //dh00:
  //


  bool SimpleILT::calculateMicroRateCoeffs(Reaction* pReact)
  {
    vector<ModelledMolecule *> unimolecularspecies;
    pReact->get_unimolecularspecies(unimolecularspecies);
    ModelledMolecule * pReactant = unimolecularspecies[0];

    int MaximumCell = pReact->getEnv().MaxCell;

    // Allocate space to hold Micro-canonical rate coefficients.
    pReact->m_CellKfmc.resize(MaximumCell, 0.0);

    // Allocate some work space for density of states.

    vector<double> cellDOS; // Density of states of equilibrim molecule.

    // Extract densities of states from molecules.

    pReactant->getCellDensityOfStates(cellDOS) ;

    // Conversion of EINF from kcal.mol^-1 to cm^-1

    int nEinf = int(pReact->get_ActivationEnergy()*kJPerMolInRC) ;

    // Calculate microcanonical rate coefficients using simple ILT expression.

    for (int i = nEinf ; i < MaximumCell ; ++i ) {
      pReact->m_CellKfmc[i] = pReact->get_PreExp() * cellDOS[i-nEinf] / cellDOS[i] ;
    }
    
    // convert forward microcanonical reaction constants to backward microcanonical reaction constants
    pReact->detailedBalance(1);

    return true;
  }
  
}//namespace
