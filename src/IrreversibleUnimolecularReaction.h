#ifndef GUARD_IrreversibleUnimolecularReaction_h
#define GUARD_IrreversibleUnimolecularReaction_h

//-------------------------------------------------------------------------------------------
//
// IrreversibleUnimolecularReaction.h
//
// Author: Struan Robertson
// Date:   30/Dec/2007
//
// This header file contains the declaration of the IrreversibleUnimolecularReaction class.
//
//-------------------------------------------------------------------------------------------

#include "Reaction.h"

namespace mesmer
{

  class IrreversibleUnimolecularReaction : public Reaction
  {
  public:

    // Constructors.
    IrreversibleUnimolecularReaction(MoleculeManager *pMoleculeManager, const MesmerEnv& Env, MesmerFlags& Flags, const char *id)
      : Reaction(pMoleculeManager, Env, Flags, id),
      m_rct1(NULL),
      m_pdt1(NULL),
      m_pdt2(NULL) {} 

    // Destructor.
    virtual ~IrreversibleUnimolecularReaction(){} ;

    // Get unimolecular species information:
    virtual int get_unimolecularspecies(std::vector<ModelledMolecule *> &unimolecularspecies) const
    {
      unimolecularspecies.push_back(m_rct1) ;
      return 1;
    } ;

    // Initialize reaction.
    virtual bool InitializeReaction(PersistPtr ppReac) ;

    // return relative reactant, product and transition state zero-point energy
    virtual double get_relative_rctZPE() const {return m_rct1->get_zpe() - getEnv().EMin;}
    virtual double get_relative_pdtZPE() const {
      double zpe = m_pdt1->get_zpe() - getEnv().EMin;
      return zpe;
    }
    virtual double get_relative_TSZPE(void) const {return m_TransitionState->get_zpe() - getEnv().EMin;};

    const int get_pdtsGrnZPE();
    
    // Calculate reaction equilibrium constant.
    virtual double calcEquilibriumConstant() ;

    // Get products cell density of states.
    void getPdtsCellDensityOfStates(std::vector<double> &cellDOS) ;

    // return the colloptrsize of the reactants
    virtual int getRctColloptrsize(){return m_rct1->get_colloptrsize();}

    // Return products
    virtual int get_products(std::vector<ModelledMolecule *> &product) const
    {
      product.push_back(m_pdt1) ;
      if(m_pdt2){
        product.push_back(m_pdt2) ;
        return 2;
      }
      return 1;
    } ;

    // Return reactants
    ModelledMolecule* get_reactants() const{return m_rct1;} ;

    // is the reaction an irreversible reaction
    virtual bool isIrreversible(){return true;};

    // get the reactant, which reacts in a first order or pseudo first order process
    virtual ModelledMolecule *get_reactant(void) const {return m_rct1;};

    // calculate the effective threshold energy for utilizing in k(E) calculations, necessary for cases
    // with a negative threshold energy
    void calcEffGrnThresholds(void);

    virtual DensityOfStatesCalculator* get_pdtsDensityOfStatesCalculator(){return m_pdt1->get_DensityOfStatesCalculator(); }

    bool calcPdtsGrainDensityOfStates(std::vector<double>& grainDOS, std::vector<double>& grainEne);

    // Calculate rovibronic canonical partition function in the grain level for product or reactant
    virtual double pdtsRovibronicGrnCanPrtnFn();
    virtual double rctsRovibronicGrnCanPrtnFn();

  private:

    // Add reaction terms to collision matrix.
    virtual void AddReactionTerms(qdMatrix *CollOptr, isomerMap &isomermap, const double rMeanOmega) ;

    // Grain averaged microcanonical rate coefficients.
    virtual void calcGrainRateCoeffs();

    // Test k(T)
    virtual void testRateConstant();

    CollidingMolecule   *m_rct1 ;                 // Reactant Molecule.
    ModelledMolecule    *m_pdt1 ;                 // Product Molecule.
    ModelledMolecule    *m_pdt2 ;                 // Subsidiary product molecule.

  } ;


}//namespace
#endif // GUARD_IrreversibleUnimolecularReaction_h