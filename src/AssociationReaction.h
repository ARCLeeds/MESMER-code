#ifndef GUARD_AssociationReaction_h
#define GUARD_AssociationReaction_h

//-------------------------------------------------------------------------------------------
//
// AssociationReaction.h
//
// Author: Struan Robertson
// Date:   30/Dec/2007
//
// This header file contains the declaration of the AssociationReaction class.
//
//-------------------------------------------------------------------------------------------

#include "Reaction.h"

namespace mesmer
{

  class AssociationReaction : public Reaction
  {
  public:

    // Constructors.
    AssociationReaction(MoleculeManager *pMoleculeManager, const MesmerEnv& Env, const char *id):
        Reaction(pMoleculeManager, Env, id),
          m_sourceMap(NULL),
        m_ERConc(0.){} ;

        // Destructor.
        virtual ~AssociationReaction(){
          delete m_sourceMap;
        };

        void putSourceMap(sourceMap *sourcemap){m_sourceMap = sourcemap ; } ;

        // Get unimolecular species information:
        virtual int get_unimolecularspecies(std::vector<ModelledMolecule *> &unimolecularspecies) const
        {
          unimolecularspecies.push_back(m_pdt1) ;
          return 1;
        } ;

        // Initialize reaction.
        virtual bool InitializeReaction(PersistPtr ppReac) ;

        // Product information:
        virtual SuperMolecule* get_bi_molecularspecies(void) const {return m_srct ; } ;

        // Get the principal source reactant (i.e. reactant not in excess).
        virtual ModelledMolecule *get_pseudoIsomer(void) const {return m_pdt1 ; } ;

        double getExcessReactantConc() const  { return m_ERConc ; } ;

  private:

    // Calculate reaction equilibrium constant.
    virtual double calcEquilibriumConstant() ;

    // Add reaction terms to collision matrix.
    virtual void AddReactionTerms(dMatrix *CollOptr, isomerMap &isomermap, const double rMeanOmega) ;

    // Read parameters requires to determine reaction heats and rates.
    virtual bool ReadRateCoeffParameters(PersistPtr ppReac) ;

    sourceMap *m_sourceMap ;

    double m_ERConc ;           // Concentration of the excess reactant

  } ;


}//namespace
#endif // GUARD_AssociationReaction_h
