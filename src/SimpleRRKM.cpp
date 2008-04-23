#include "SimpleRRKM.h"


using namespace std;
using namespace Constants;
namespace mesmer
{
	//************************************************************
	//Global instance, defining its id (usually the only instance)
	SimpleRRKM theSimpleRRKM("Simple RRKM");
	//************************************************************

	bool SimpleRRKM::calculateMicroRateCoeffs(Reaction* pReact, std::vector<double>& TSFlux)
	{
		vector<ModelledMolecule *> unimolecularspecies;
		pReact->get_unimolecularspecies(unimolecularspecies);

		ModelledMolecule *p_rct = unimolecularspecies[0];

		TransitionState* pTS = pReact->get_TransitionState();
		if(!pTS)
		{
			cerr << "Lack of transition state in reaction " << pReact->getName() << " for Simple RRKM" << endl;
			return false;
		}

    // get MaxCell from MesmerEnv structure via Reaction class 
		int MaximumCell = pReact->getEnv().MaxCell;

		// Allocate space to hold Micro-canonical rate coefficients and initialize elements to zero.
		TSFlux.resize(MaximumCell, 0.0);

		// Allocate some work space for density of states.

		vector<double> TScellDOS; // Transition state density of states.
		vector<double> rctCellDOS; // Density of states in the well (reactant)

		// Extract densities of states from molecules.
		p_rct->getCellDensityOfStates(rctCellDOS) ;
		pTS->getCellDensityOfStates(TScellDOS) ;

		int thresholdEnergy = int(pReact->get_ThresholdEnergy()) ;

		if (pReact->thereIsTunnelling()) { // with tunneling

			vector<double> TunnelingProbability;

			pReact->calculateTunnelingCoeffs(TunnelingProbability);

			for (int i = 0; i < MaximumCell ; ++i) {
				// Integrate transition state density of states.
				double SumOfStates = 0.0;
				for (int j = 0; j <= i; ++j) 
					SumOfStates += TunnelingProbability[i-j] * TScellDOS[j];

				// Calculate microcanonical rate coefficients using RRKM expression with tunneling correction.
				TSFlux[i] = SumOfStates * SpeedOfLight_in_cm / rctCellDOS[i];
			}
		}
		else{ // without tunneling
			double SumOfStates = 0.0;
			for (int i = thresholdEnergy, j = 0 ; i < MaximumCell ; ++i, ++j ) {
				// Integrate transition state density of states.
				SumOfStates += TScellDOS[j];

				// Calculate microcanonical rate coefficients using RRKM expression.
				TSFlux[i] = SumOfStates * SpeedOfLight_in_cm / rctCellDOS[i];
			}
		}

		return true;
	}

}//namespace
