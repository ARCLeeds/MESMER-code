//-------------------------------------------------------------------------------------------
//
// ExchangeReaction.cpp
//
// Author: Struan Robertson
// Date:   Aug/2019
//
// This file contains the implementation of the ExchangeReaction class.
//
//-------------------------------------------------------------------------------------------
#include <limits>
#include "ExchangeReaction.h"
#include "gStructure.h"
#include "gWellProperties.h"
#include "PriorDistFragmentation.h"

using namespace Constants;
using namespace std;
using namespace mesmer;

namespace mesmer
{
  // Read the Molecular data from input stream.
  bool ExchangeReaction::InitializeReaction(PersistPtr ppReac)
  {
    m_ppPersist = ppReac;

    PersistPtr ppReactantList = ppReac->XmlMoveTo("reactantList");
    if (!ppReactantList)
      ppReactantList = ppReac; //Be forgiving; we can get by without a reactantList element

    PersistPtr ppReactant1 = ppReactantList->XmlMoveTo("reactant");      // Read reactant details.
    Molecule* pMol1 = GetMolRef(ppReactant1);
    if (!pMol1) {
      cerr << "Cannot find 1st reactant molecule definition for association reaction " << getName() << ".";
      return false;
    }
    PersistPtr ppReactant2 = ppReactant1->XmlMoveTo("reactant");
    Molecule* pMol2 = GetMolRef(ppReactant2);
    if (!pMol2)
    {
      cerr << "Cannot find 2nd reactant molecule definition for association reaction " << getName() << ".";
      return false;
    }

    // if deficientReactantLocation=true, then pMol1 (the first rct
    // in the XML input) is the deficient reactant (m_rct1)

    Molecule* tmp_rct1 = pMol1;
    Molecule* tmp_rct2 = pMol2;

    if (deficientReactantLocation) {
      m_rct1 = tmp_rct1;
      m_rct2 = tmp_rct2;
    }
    else {
      m_rct1 = tmp_rct2;
      m_rct2 = tmp_rct1;
    }

    if (!m_rct1) {
      cerr << "the deficient reactant in the association reaction is undefined" << endl;
      return false;
    }
    if (!m_rct2) {
      cerr << "the excess reactant in the association reaction is undefined" << endl;
      return false;
    }

    PersistPtr ppProductList = ppReac->XmlMoveTo("productList");
    if (!ppProductList)
      ppProductList = ppReac; //Be forgiving; we can get by without a productList element

    PersistPtr ppProduct1 = ppProductList->XmlMoveTo("product");     // Read product details. Save them as type Molecule
    if (ppProduct1) {
      pMol1 = GetMolRef(ppProduct1);
      if (pMol1) {
        m_pdt1 = pMol1;
      }
      else {
        cerr << "Exchange reaction" << getName() << " has no products defined.";
      }

      PersistPtr ppProduct2 = ppProduct1->XmlMoveTo("product");
      if (ppProduct2) {
        pMol2 = GetMolRef(ppProduct2);
        if (pMol2) {
          m_pdt2 = pMol2;
        }
        else {
          cerr << "Exchange reaction " << getName() << " has only one product defined.";
        }
      }
    }

    // Determine fragmentation model.
    PersistPtr ppDstbn = ppReac->XmlMoveTo("me:FragmentDist");
    if (ppDstbn) {
      const char* ptxt = ppDstbn->XmlReadValue("xsi:type", optional); ;
      string fragMod(ptxt);
      if (fragMod == "me:modPrior")
        m_fragDist = new modPriorDist(ppDstbn, this->getName());
      else
        m_fragDist = new priorDist();
    }
    else {
      m_fragDist = new priorDist();
    }

    // Read heat of reaction and rate parameters.
    if (!ReadRateCoeffParameters(ppReac)) 
      return false;

    // Check the transistion state is defined. 
    if (!m_TransitionState)
      return false;

    return true;
  }

  double ExchangeReaction::calcEquilibriumConstant() {   // Calculate reaction equilibrium constant.
    // equilibrium constant:
    double Keq(0.0);
    const double beta = getEnv().beta;

    vector<double> cellEne;
    getCellEnergies(m_rct1->getEnv().MaxCell, m_rct1->getEnv().CellSize, cellEne);

    // Rovibronic partition function for products/reactants.
    vector<double> tmpDOS;
    m_rct1->getDOS().getCellDensityOfStates(tmpDOS);
    double Qrcts = canonicalPartitionFunction(tmpDOS, cellEne, beta);
    tmpDOS.clear();
    m_rct2->getDOS().getCellDensityOfStates(tmpDOS);
    Qrcts *= canonicalPartitionFunction(tmpDOS, cellEne, beta);

    m_pdt1->getDOS().getCellDensityOfStates(tmpDOS);
    double Qpdts = canonicalPartitionFunction(tmpDOS, cellEne, beta);
    tmpDOS.clear();
    m_pdt2->getDOS().getCellDensityOfStates(tmpDOS);
    Qpdts *= canonicalPartitionFunction(tmpDOS, cellEne, beta);

    // Rovibronic partition function for reactants/products multiplied by translation contribution.
    Qrcts *= translationalContribution(m_rct1->getStruc().getMass(), m_rct2->getStruc().getMass(), beta);
    Qpdts *= translationalContribution(m_pdt1->getStruc().getMass(), m_pdt2->getStruc().getMass(), beta);

    Keq = Qpdts / Qrcts;

    // Heat of reaction: use heat of reaction to calculate the zpe weighing of different wells.
    const double HeatOfReaction = getHeatOfReaction();
    Keq *= exp(-beta * HeatOfReaction);

    return Keq;
  }

  // Add exchange reaction terms to collision matrix.
  void ExchangeReaction::AddReactionTerms(qdMatrix *CollOptr, molMapType &isomermap, const double rMeanOmega)
  {
    // Locate isomers in system matrix.
    const size_t rctLocation = (*m_sourceMap)[m_rct1];
    const size_t pdtLocation = isomermap[m_pdt1];

    // Need to know the number of grouped grains in product.
    const size_t pShiftedGrains(m_pdt1->getColl().reservoirShift());

    const size_t pColloptrsize = m_pdt1->getColl().get_colloptrsize() + pShiftedGrains;

    // Get equilibrium constant.
    const qd_real Keq = qd_real(calcEquilibriumConstant());

    // Get TS Boltzmann distribution for partition of rate.
    vector<double> TStPopFrac; // Population fraction of the transition state.
    m_TransitionState->getColl().set_colloptrsize(pColloptrsize);
    m_TransitionState->getColl().normalizedGrnBoltzmannDistribution(TStPopFrac);

    // Call high pressure rate method because exchange reaction rate coefficients
    // do not depend on pressure. The extra logic is to control output. 
    bool writeStatus = getFlags().testRateConstantEnabled;
    getFlags().testRateConstantEnabled = false;
    HighPresRateCoeffs(NULL);
    getFlags().testRateConstantEnabled = writeStatus;

    qd_real AssocRateCoeff(m_MtxGrnKf[0]), qdMeanOmega(rMeanOmega);

    // Calculate the weighted sum of the energy partition distribution.
    m_fragDist->initialize(this);
    vector<double> fragRate;
    for (size_t i(0); i < pColloptrsize; ++i) {

    }

    const int pdtRxnOptPos(pdtLocation - pShiftedGrains);

    const size_t jj = rctLocation;
    (*CollOptr)[jj][jj] -= qdMeanOmega * AssocRateCoeff;
    for (size_t i(0), j(0); i < pColloptrsize; ++i, ++j) {
      size_t ii(pdtRxnOptPos + i);
      //int kk(i - pShiftedGrains);
      //qd_real Flux(m_GrainFlux[j]), dos(pdtDOS[i]), addPop(adductPopFrac[kk]);
      (*CollOptr)[ii][ii] -= qdMeanOmega * AssocRateCoeff/Keq;                  // Loss of the adduct to the source
      (*CollOptr)[jj][ii] = qdMeanOmega * AssocRateCoeff / sqrt(qd_real(Keq));  // Reactive gain of the source
      (*CollOptr)[ii][jj] = (*CollOptr)[jj][ii];                                // Reactive gain (symmetrization)
    }

    // Return any resources used.
    m_fragDist->clear();

  }

  // Calculate high pressure rate coefficients at current T.
  void ExchangeReaction::HighPresRateCoeffs(vector<double> *pCoeffs) {

    double k_forward(0.0);
    const double beta = getEnv().beta;

    string mrcID = string(m_pMicroRateCalculator->getID());

    if (mrcID == "CanonicalRateCoefficient") {
      m_pMicroRateCalculator->calculateMicroCnlFlux(this);
      k_forward = m_CellFlux[0];
    }
    else {
      throw(std::runtime_error(string("The irreversible exchange reaction " + getName() + " is defined without either a transition state or Arrhenius parameters.\n")));
    }

    // Save high pressure rate coefficient for use in the construction of the collision operator.
    m_MtxGrnKf.clear();
    m_MtxGrnKf.push_back(k_forward*m_ERConc);

    if (pCoeffs) {
      pCoeffs->push_back(k_forward);
      const double Keq = calcEquilibriumConstant();
      if (!IsNan(Keq)) {
        pCoeffs->push_back(k_forward / Keq);
        pCoeffs->push_back(Keq);
      }
    }
    else if (getFlags().testRateConstantEnabled) {
      const double temperature = 1. / (boltzmann_RCpK * beta);
      stest << endl << "Canonical pseudo first order rate constant of irreversible reaction "
        << getName() << " = " << k_forward*m_ERConc << " s-1 (" << temperature << " K)" << endl;
      stest << "Canonical bimolecular rate constant of irreversible reaction "
        << getName() << " = " << k_forward << " cm^3/molec/s (" << temperature << " K)" << endl;
    }
  }

  const int ExchangeReaction::get_rctsGrnZPE() {
    double grnZpe = (m_rct1->getDOS().get_zpe() + m_rct2->getDOS().get_zpe() - getEnv().EMin) / getEnv().GrainSize; //convert to grains
    if (grnZpe < 0.0)
      cerr << "Grain zero point energy has to be a non-negative value.";

    return int(grnZpe);
  }

  void ExchangeReaction::calcEffGrnThresholds(void) {
    int TS_en = get_fluxGrnZPE();// see the comments in calcEffGrnThresholds under AssociationReaction.cpp  
    int rct_en = get_rctsGrnZPE();

    double thresh = get_ThresholdEnergy();
    if (thresh < 0.0) {
      set_EffGrnFwdThreshold(0 / getEnv().GrainSize);
    }
    else {
      set_EffGrnFwdThreshold((TS_en - rct_en) / getEnv().GrainSize);
    }
  }

  void ExchangeReaction::calcFluxFirstNonZeroIdx(void) {
    double thresh = get_ThresholdEnergy();
    if (thresh < 0.0) { m_GrnFluxFirstNonZeroIdx = int(-thresh / getEnv().GrainSize); }
    else { m_GrnFluxFirstNonZeroIdx = 0; }
  }

}//namespace
