//-------------------------------------------------------------------------------------------
//
// ReactionManager.cpp
//
// Author: Struan Robertson
// Date:   11/Feb/2003
//
// This file contains the implementation of the ReactionManager class.
//
//-------------------------------------------------------------------------------------------
#include "ReactionManager.h"

using namespace Constants ;
using namespace std ;

namespace mesmer
{
  //
  // Add a new reaction to the map.
  //
  bool ReactionManager::addreactions(PersistPtr ppReacList)
  {
    PersistPtr ppReac = ppReacList->XmlMoveTo("reaction");
    while(ppReac)
    {
      //
      // Create a new Reaction.
      //
      Reaction *preaction = new Reaction(m_pMoleculeManager) ;

      //
      // Initialize Reaction from input stream.
      //
      if(!preaction->InitializeReaction(ppReac)){
        delete preaction;
        return false;
      }

      //preaction->put_verbosity(true) ;

      //
      // Add reaction to map.
      //
      m_reactions.push_back(preaction) ;

      ppReac = ppReac->XmlMoveTo("reaction");
    }

    return true;
  }

  int ReactionManager::Connectivity(Molecule* pReactant, Molecule* pProduct)
  {
    return -1;
  }

  void ReactionManager::BuildSystemCollisionOperator(const double beta, const MesmerEnv &mEnv)
  {
    //
    // Find all the unique wells and lowest zero point energy.
    //
    Reaction::isomerMap isomers ; // Maps the location of reactant collision operator in the system matrix.
    double minEnergy(0) ; //this is the minimum of ZPE amongst all wells
    Molecule *pBathGasMolecule = m_pMoleculeManager->get_BathGasMolecule();

    // populate isomerMap with unimolecular species
    for (size_t i(0) ; i < size() ; ++i) {

      vector<CollidingMolecule *> unimolecules ;

      int flag1 = m_reactions[i]->get_unimolecularspecies(unimolecules) ;

      if (flag1 > 0){ // association, dissociation or isomerization
        for (size_t i(0) ; i < unimolecules.size() ; ++i) {
          CollidingMolecule *pCollidingMolecule = unimolecules[i] ;
          if(isomers.find(pCollidingMolecule) == isomers.end()){ // New isomer
            isomers[pCollidingMolecule] = 0 ; //initialize to a trivial location
            minEnergy = min(minEnergy, pCollidingMolecule->get_zpe()) ;
          }
        }
      }
      else{
        stringstream errorMsg;
        // Does this kind of reaction ever exist? CHL
        errorMsg << "Reaction " << m_reactions[i]->getName() << " is invalid without any product and reactant." << endl;
        obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
      }
    }

    //
    // Shift all wells to the same origin, calculate the size of the system collision operator,
    // calculate the mean collision frequency and initialize all collision operators.
    //
    int msize(0) ; // size of the collision matrix
    double meanomega(0.0) ;
    Reaction::isomerMap::iterator isomeritr = isomers.begin() ;
    for (; isomeritr != isomers.end() ; ++isomeritr) {

      CollidingMolecule *isomer = isomeritr->first ;
      isomeritr->second = msize ; //set location

      double zpe = (isomer->get_zpe()) - minEnergy ; // cell zpe related with the minimum of all wells
      int grnZpe = int(zpe * KcalPerMolToRC / mEnv.GrainSize) ; //convert to grain

      {stringstream errorMsg;
      errorMsg << "_2007_11_09__14_10_21_ grnZpe = " << grnZpe << ", zpe = " << zpe << ", minEnergy = " << minEnergy << endl;
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}

      isomer->set_grnZpe(grnZpe) ; //set grain ZPE (related with the minimum of all wells)
      int colloptrsize = mEnv.MaxGrn  - grnZpe ;
      isomer->set_colloptrsize(colloptrsize) ;
      msize += colloptrsize ;

      isomer->initCollisionOperator(beta, pBathGasMolecule, mEnv) ;
      meanomega += isomer->get_collisionFrequency() ;
    }
    meanomega /= isomers.size();

    //
    // Find all source terms. Note: A source term is probably the only deficient reactant that initiates the whole process
    // of reactions in the master equation. In this case we think there may be more than one source terms. CHL
    //
    Reaction::sourceMap sources ; // Maps the location of source in the system matrix.
    for (size_t i(0) ; i < size() ; ++i) {

      SuperMolecule *pSuperMolecule = new SuperMolecule;
      if (m_reactions[i]->get_bi_molecularspecies(pSuperMolecule) == 2 &&
          sources.find(pSuperMolecule) == sources.end()){ // New source
        ++msize ;
        sources[pSuperMolecule] = msize ;
      }
    }

    cout << endl << "Size of the collision matrix: " << msize << endl << endl ;

    // Allocate space for system collision operator.

    m_pSystemCollisionOperator = new dMatrix(msize) ;

    // Insert collision operators for individual wells.
    for (isomeritr = isomers.begin() ; isomeritr != isomers.end() ; ++isomeritr) {

      CollidingMolecule *isomer = isomeritr->first ;
      int colloptrsize = isomer->get_colloptrsize() ;
      double omega = isomer->get_collisionFrequency() ;
      int idx = isomeritr->second ;

      isomer->copyCollisionOperator(m_pSystemCollisionOperator, colloptrsize, idx, omega/meanomega, mEnv) ;

    }

    // Add connecting rate coefficients.
    for (size_t i(0) ; i < size() ; ++i) {
        m_reactions[i]->AddMicroRates(m_pSystemCollisionOperator,isomers,sources,1.0/meanomega, mEnv) ;
    }
  }

  void ReactionManager::diagCollisionOperator()
  {
    // Allocate space for eigenvalues.
    const int smsize = int(m_pSystemCollisionOperator->size()) ;
    vector<double> rr(smsize, 0.0);

    m_pSystemCollisionOperator->diagonalize(&rr[0]) ;

    // Print out the first ten eigen values.

    cout << endl ;

    for (int i = smsize-10 ; i < smsize; ++i) {
      formatFloat(cout, rr[i], 6, 15) ;
      cout << endl ;
    }

    cout << endl ;
  }

}//namespace
