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
// This class describes a linearized association reaction in which one reactant is in such
// excess that reaction does not significantly alter its concentration. The reactant with
// the smaller concentration is deemed to be the pseudo-isomer of the reaction. Following
// regular isomerization, a number of reaction properties are delegated to the pseudo-isomer,
// e.g. the zero point energy location of the associating pair. Other quantities, such as
// the combined density of states, are properties of the reaction and are held at that level.
//
//-------------------------------------------------------------------------------------------
#include "Reaction.h"

using namespace Constants ;
using namespace std;
using namespace mesmer;

namespace mesmer
{

  class AssociationReaction : public Reaction
  {
  public:

    // Constructors.
    AssociationReaction(MoleculeManager *pMoleculeManager, const MesmerEnv& Env, MesmerFlags& Flags, const char *id, bool isReactant)
      :Reaction(pMoleculeManager, Env, Flags, id),
      m_sourceMap(NULL),
      m_rct1(NULL),
      m_rct2(NULL),
      m_pdt1(NULL),
      deficientReactantLocation(isReactant),
      m_ERConc(0.)
    {}

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

    // Get product information:
    virtual int get_products(std::vector<ModelledMolecule *> &unimolecularspecies) const
    {
      unimolecularspecies.push_back(m_pdt1) ;
      return 1;
    } ;

    // return the colloptrsize of the reactants
    virtual int getRctColloptrsize(){return 1;}

    // Initialize reaction.
    virtual bool InitializeReaction(PersistPtr ppReac) ;

    // Get the principal source reactant (i.e. reactant not in excess).
    virtual ModelledMolecule *get_pseudoIsomer(void) const {return m_rct1 ; } ;
    virtual ModelledMolecule *get_reactant(void) const {return m_rct1;};
    virtual ModelledMolecule *get_excessReactant(void) const {return m_rct2 ; } ;

    // return relative reactant, product and transition state zero-point energy
    virtual double get_relative_rctZPE() const { return m_rct1->get_zpe() + m_rct2->get_zpe() - getEnv().EMin; }
    virtual double get_relative_pdtZPE() const { return m_pdt1->get_zpe() - getEnv().EMin; }
    virtual double get_relative_TSZPE(void) const { return m_TransitionState->get_zpe() - getEnv().EMin; };

    // Calculate reaction equilibrium constant.
    virtual double calcEquilibriumConstant() ;

    // Is reaction equilibrating and therefore contributes
    // to the calculation of equilibrium fractions.
    virtual bool isEquilibratingReaction(double &Keq, ModelledMolecule **rct, ModelledMolecule **pdt) ;

    // Get reactants cell density of states.
    void getRctsCellDensityOfStates(std::vector<double> &cellDOS) ;

    // Get reactants grain ZPE
    const int get_rctsGrnZpe(void);

    // calculate the effective threshold energy for utilizing in k(E) calculations, necessary for cases
    // with a negative threshold energy
    void calculateEffectiveGrainedThreshEn(void);

    // Get cell offset for the reactants
    int get_cellOffset(void) {
      double modulus = fmod(m_rct1->get_zpe() + m_rct2->get_zpe() - getEnv().EMin, getEnv().GrainSize);
      return int(modulus) ;
    } ;

    virtual DensityOfStatesCalculator* get_rctsDensityOfStatesCalculator(){return get_pseudoIsomer()->get_DensityOfStatesCalculator(); }

    bool calcRctsGrainDensityOfStates(std::vector<double>& grainDOS, std::vector<double>& grainEne);

    double rctsRovibronicGrnCanPrtnFn();

  private:

    // Add reaction terms to collision matrix.
    virtual void AddReactionTerms(qdMatrix *CollOptr, isomerMap &isomermap, const double rMeanOmega) ;

    // Read parameters requires to determine reaction heats and rates.
    virtual bool ReadRateCoeffParameters(PersistPtr ppReac) ;

    // Grain averaged microcanonical rate coefficients.
    virtual void calcGrainRateCoeffs();

    // Test k(T)
    virtual void testRateConstant();

    sourceMap *m_sourceMap ;

    // Reaction composition:

    ModelledMolecule    *m_rct1 ;   // Reactant Molecule.
    ModelledMolecule    *m_rct2 ;   // Subsidiary reactant molecule.
    CollidingMolecule   *m_pdt1 ;   // Product Molecule.

    bool deficientReactantLocation; // true if 1st rct in XML file is deficient false if 2nd reactant is deficient
    double               m_ERConc ; // Concentration of the excess reactant

  } ;


}//namespace
#endif // GUARD_AssociationReaction_h
