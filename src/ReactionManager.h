#ifndef GUARD_ReactionManager_h
#define GUARD_ReactionManager_h

//-------------------------------------------------------------------------------------------
//
// ReactionManager.h
//
// Author: Struan Robertson
// Date:   11/Feb/2003
//
// This header file contains the declaration of the ReactionManager class.
// This class will contain the reactions that go to make up a system.
//
//-------------------------------------------------------------------------------------------

#include "AssociationReaction.h"
#include "IrreversibleUnimolecularReaction.h"
#include "IsomerizationReaction.h"
#include "IrreversibleExchangeReaction.h"

namespace mesmer
{
  class ReactionManager
  {
  public:

    // Type defs
    typedef  size_t  size_type ;
    typedef std::map<std::string , double> populationMap ;
    typedef std::map<Reaction* , int, Reaction::ReactionPtrLess> sinkMap ;

    ReactionManager(MoleculeManager *pMoleculeManager);

    // Destructor.
    ~ReactionManager()
    {
      if (m_reactionOperator) delete m_reactionOperator;
      vector<Reaction*>::iterator iter;
      for(iter=m_reactions.begin();iter!=m_reactions.end();++iter)
        delete *iter;
      m_reactions.clear();
    }

    // Add a new reaction to the map.
    bool addreactions(PersistPtr ReacList, const MesmerEnv& mEnv, MesmerFlags& mFlags) ;

    // Remove a reaction from the map.
    void remove(){} ;

    void resetCalcFlags();

    // Total number of reaction in map.
    size_type size() const {return m_reactions.size() ; } ;

    // Find a particular reaction.
    Reaction*       operator[](const size_type i)       { return m_reactions[i] ; } ;
    const Reaction* operator[](const size_type i) const { return m_reactions[i] ; } ;

    // Find a reaction from its id
    Reaction* find(const std::string& id) const ;

    // Build reaction operator for system.
    bool BuildReactionOperator(MesmerEnv &mEnv, MesmerFlags& mFlags) ;

    // Diagonalize the reaction operator.
    void diagReactionOperator(const MesmerFlags &mFlags, const int precision) ;

    // Calculate the time evolution of the system
    bool timeEvolution(MesmerFlags& mFlags);

    // Set Initial population for individual species
    void setInitialPopulation(PersistPtr);

    bool calculateEquilibriumFractions(const double beta);

    bool BartisWidomPhenomenologicalRates(dMatrix& rates, MesmerFlags& mFlags,PersistPtr ppBase);

    double calcChiSquare(const dMatrix& mesmerRates, vector<conditionSet>& expRates);

    void constructBasisMatrix(void);

  private:

    std::vector<Reaction *> m_reactions ;

    MoleculeManager        *m_pMoleculeManager ;

    qdMatrix               *m_reactionOperator ;
    qdMatrix               *m_eigenvectors;
    std::vector<qd_real>    m_eigenvalues;

    // Reaction operator after similarity transformation by block diagonal U, which is U^-1 M' U.
    qdMatrix               *m_basisMatrix;

    qdMatrix               *m_reducedReactionOperator;
    qdMatrix               *m_reducedEigenvectors;
    std::vector<qd_real>    m_reducedEigenvalues;

    std::vector<double>     m_eqVector;

    // Maps the location of individual reactant collision operator and source terms in the reaction operator.
    Reaction::molMapType    m_isomers;
    Reaction::molMapType    m_sources;
    sinkMap                 m_sinkRxns;
    populationMap           m_initialPopulations;

    // map modelled molecules (isomers + sources) with their sequence in the EqMatrix and Rate Coefficient matrix
    Reaction::molMapType    m_SpeciesSequence;

    sinkMap m_SinkSequence;

    double m_meanOmega;

    bool punchSymbolGathered;

    // Extract molecule information from XML stream.
    bool GetMoleculeInfo(PersistPtr pp, std::string& MolName, std::string& MolType) ;

    // sets grain parameters and determines system environment
    bool SetGrainParams(MesmerEnv &mEnv, const MesmerFlags& mFlags, const double minEne, const double maxEne);

    bool produceInitialPopulationVector(vector<double>& initDist);

    bool produceEquilibriumVector();

    void printReactionOperator(const MesmerFlags &mFlags);

  } ;
}//namespace

#endif // GUARD_ReactionManager_h
