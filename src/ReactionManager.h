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
#include "DissociationReaction.h"
#include "IsomerizationReaction.h"
#include "ExchangeReaction.h"

namespace mesmer
{
  class ReactionManager
  {
  public:

    // Type defs
    typedef  size_t  size_type ;

    ReactionManager(MoleculeManager *pMoleculeManager):
    m_reactions(),
        m_pMoleculeManager(pMoleculeManager),
        m_pSystemCollisionOperator(0),
        m_minEnergy(0.0)
    {};

    // Destructor.
    ~ReactionManager(){} ;

    // Add a new reaction to the map.
    bool addreactions(PersistPtr ReacList, const MesmerEnv& Env) ;

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

    // Interrogates the (virtual) connectivity matrix, returning the reaction
    // index of the reaction (one based) connecting pProduct and pReactant
    // if both are CollidingMolecules
    // 0 if reactant and product are the same and are a CollidingMolecule
    // -1 otherwise
    int Connectivity(Molecule* pReactant, Molecule* pProduct);

    // Build collision operator for system.
    bool BuildSystemCollisionOperator(const MesmerEnv &Env) ;

    // Diagonalize the collision operator.
    void diagCollisionOperator(const MesmerEnv &Env) ;

  private:

    std::vector<Reaction *> m_reactions ;

    MoleculeManager        *m_pMoleculeManager ;

    dMatrix                *m_pSystemCollisionOperator ;
    
    double m_minEnergy;

    // Default Constructor.
    //ReactionManager() {} ;

    // Extract molecule information from XML stream.
    bool GetMoleculeInfo(PersistPtr pp, std::string& MolName, std::string& MolType) ;

  } ;
}//namespace

#endif // GUARD_ReactionManager_h
