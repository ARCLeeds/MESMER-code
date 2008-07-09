//-------------------------------------------------------------------------------------------
//
// AssociationReaction.cpp
//
// Author: Struan Robertson
// Date:   30/Dec/2007
//
// This file contains the implementation of the AssociationReaction class.
//
//-------------------------------------------------------------------------------------------
#include <limits>
#include "AssociationReaction.h"
#include <math.h>

using namespace Constants ;
using namespace std;

namespace mesmer
{
  //
  // Read the Molecular for association reaction data from input stream.
  // Note: the convention adopted here is that there are two reactants
  // and one product (adduct).
  //
  bool AssociationReaction::InitializeReaction(PersistPtr ppReac)
  {
    m_ppPersist = ppReac;

    // Read reactant details.

    PersistPtr ppReactant1  = ppReac->XmlMoveTo("reactant");
    Molecule* pMol1 = GetMolRef(ppReactant1);
    if(!pMol1){
      cerr << "Cannot find 1st reactant molecule definition for association reaction " << getName() << ".";
      return false;
    }
    PersistPtr ppReactant2  = ppReactant1->XmlMoveTo("reactant");
    Molecule* pMol2 = GetMolRef(ppReactant2);
    if(!pMol2)
    {
      cerr << "Cannot find 2nd reactant molecule definition for association reaction " << getName() << ".";
      return false;
    }

    // Put the CollidingMolecule into m_rct1, even if it is second in datafile

    CollidingMolecule* pColMol = dynamic_cast<CollidingMolecule*>(pMol1);
    if(pColMol){
      m_rct2 = dynamic_cast<ModelledMolecule*>(pMol2);
    } else {
      pColMol = dynamic_cast<CollidingMolecule*>(pMol2);
      if(!pColMol){
        cerr << "At least one of the reactants has to be a colliding molecule";
        return false;
      }
      m_rct2 = dynamic_cast<ModelledMolecule*>(pMol1);
    }
    m_rct1 = pColMol;

    // SuperMolecule section --- to be removed. ------------------------------
    string id; //shoud not set any name for it.
    SuperMolecule* pSupMol = NULL;
    while(m_pMoleculeManager->GetNextMolecule(id, pSupMol)){ // get next SuperMolecule
      // if found a SuperMolecule
      ModelledMolecule* rm1 = pSupMol->getMember1();
      ModelledMolecule* rm2 = pSupMol->getMember2();
      if (!rm1 && !rm2){// there is no data inside, occupy it!
        pSupMol->setMembers(m_rct1, m_rct2);
        m_srct = pSupMol;
        break;
      }
    }
    if (!pSupMol){
      cerr << "No SuperMolecule was found.";
      // there will always at least one SuperMolecule in m_molmap, check the end of addmol()
      // in MoleculeManager.cpp.
    }
    // SuperMolecule section --- to be removed. ------------------------------

    //Read product details.

    PersistPtr ppProduct1 = ppReac->XmlMoveTo("product");
    pMol1 = GetMolRef(ppProduct1);
    if (!pMol1) {
      cerr << "Cannot find product molecule definition for association reaction " << getName() << ".";
      return false;
    }

    // Save product as CollidingMolecule.

    pColMol = dynamic_cast<CollidingMolecule*>(pMol1);
    if(pColMol){
      m_pdt1 = pColMol;
    } else {
      cerr << "Isomer product must be a colliding molecule";
      return false;
    }

    // Read the transition state (if present)
    PersistPtr ppTransitionState = ppReac->XmlMoveTo("me:transitionState") ;
    if (ppTransitionState)
    {
      TransitionState* pTrans = dynamic_cast<TransitionState*>(GetMolRef(ppTransitionState,"transitionState"));
      if(pTrans) m_TransitionState = pTrans;
    }

    // Read heat of reaction and rate parameters.

    return ReadRateCoeffParameters(ppReac) ;
  }

  //
  // Add (REVERSIBLE) association reaction terms to collision matrix.
  //
  void AssociationReaction::AddReactionTerms(qdMatrix      *CollOptr,
    isomerMap    &isomermap,
    const double rMeanOmega)
  {
    // Get densities of states of the adduct for detailed balance.
    vector<double> pdtDOS;
    m_pdt1->getGrainDensityOfStates(pdtDOS) ;

    // Locate isomers in system matrix.
    const int pdtLoc =      isomermap[m_pdt1] ;
    const int jj     = (*m_sourceMap)[m_srct] ;

    // Get equilibrium constant.
    const double Keq = calcEquilibriumConstant() ;

    // Get Boltzmann distribution for detailed balance.
    const int MaximumGrain = getEnv().MaxGrn ;
    vector<double> adductPopFrac ; // Population fraction of the adduct

    const int pdtGrainZPE = m_pdt1->get_grnZpe();
    m_pdt1->normalizedBoltzmannDistribution(adductPopFrac, MaximumGrain - pdtGrainZPE) ;

    qd_real DissRateCoeff(0.0) ;

    const int TSFluxGrainZPE  = getTSFluxGrnZPE();

    for ( int i = TSFluxGrainZPE, j = 0; i < MaximumGrain; ++i, ++j) {
      int ll(i - pdtGrainZPE);
      int ii(pdtLoc + ll) ;

      (*CollOptr)[ii][ii] -= qd_real(rMeanOmega * m_GrainTSFlux[j] / pdtDOS[ll]);                                // Loss of the adduct to the source
      (*CollOptr)[jj][ii]  = qd_real(rMeanOmega * m_GrainTSFlux[j] * sqrt(adductPopFrac[ll] * Keq) / pdtDOS[ll]);// Reactive gain of the source
      (*CollOptr)[ii][jj]  = (*CollOptr)[jj][ii] ;                                                      // Reactive gain (symmetrization)
      DissRateCoeff       += qd_real(m_GrainTSFlux[j] * adductPopFrac[ll] / pdtDOS[ll]);
    }
    (*CollOptr)[jj][jj] -= qd_real(rMeanOmega * DissRateCoeff * Keq);       // Loss of the source from detailed balance.
  }

  //
  // Calculate reaction equilibrium constant for the general reaction
  //        A + B  <===> C
  //
  double AssociationReaction::calcEquilibriumConstant() {

    // equilibrium constant:
    double Keq(0.0) ;
    const double beta = getEnv().beta ;

    // partition function for each reactant
    double Qrcts = m_srct->rovibronicGrnCanPrtnFn();

    // rovibronic partition function for reactants multiplied by translation contribution
    Qrcts *= translationalContribution(m_rct1->getMass(), m_rct2->getMass(), beta);

    // rovibronic partition function for product
    const double Qpdt1 = m_pdt1->rovibronicGrnCanPrtnFn() ;

    Keq = Qpdt1 / Qrcts;

    /* Electronic degeneracies were already accounted for in DOS calculations */

    // Heat of reaction: use heat of reaction to calculate the zpe weighing of different wells
    const double HeatOfReaction = getHeatOfReaction() ;
    const double _expon = -beta * HeatOfReaction;
    Keq *= exp(_expon) ;

    const double excess = m_srct->getExcessReactantConc();
    Keq *= excess ;
    //
    // K_eq = ( [C]/[A][B] ) * [A] = [C]/[B]
    //
    // where [A] is the reactant what is in excess (seen as constant).
    // Therefore, the K_eq here is essentially the pseudo-first-order equilibrium constant.

    return (double) Keq ;

  }

  // Read parameters requires to determine reaction heats and rates.
  bool AssociationReaction::ReadRateCoeffParameters(PersistPtr ppReac) {

    // Read the heat of reaction (if present).
      const char* pHeatRxntxt = ppReac->XmlReadValue("me:HeatOfReaction",false);
    if (pHeatRxntxt){
      stringstream s1(pHeatRxntxt);
      double value = 0.0; s1 >> value ; setHeatOfReaction(value);
    } else { // Calculate heat of reaction.
      setHeatOfReaction(get_relative_pdtZPE(), get_relative_rctZPE());
    }

    const char* pActEnetxt = ppReac->XmlReadValue("me:activationEnergy", false);
    if (pActEnetxt)
    {
      PersistPtr ppActEne = ppReac->XmlMoveTo("me:activationEnergy") ;
      double value = 0.0;
      stringstream s2(pActEnetxt); s2 >> value ;
      const char* pLowertxt = ppActEne->XmlReadValue("lower", false);
      const char* pUppertxt = ppActEne->XmlReadValue("upper", false);
      const char* pStepStxt = ppActEne->XmlReadValue("stepsize", false);
      if (pLowertxt && pUppertxt){
        double valueL(0.0), valueU(0.0), stepsize(0.0);
        stringstream s3(pLowertxt), s4(pUppertxt), s5(pStepStxt); s3 >> valueL; s4 >> valueU; s5 >> stepsize;
        set_ThresholdEnergy(value, valueL, valueU, stepsize);
      }
      else{
        set_ThresholdEnergy(value);
      }
    }

    const char* pPreExptxt = ppReac->XmlReadValue("me:preExponential", false);
    if (pPreExptxt)
    {
      PersistPtr ppPreExponential = ppReac->XmlMoveTo("me:preExponential") ;
      double value = 0.0;
      stringstream s2(pPreExptxt); s2 >> value ;
      const char* pLowertxt = ppPreExponential->XmlReadValue("lower", false);
      const char* pUppertxt = ppPreExponential->XmlReadValue("upper", false);
      const char* pStepStxt = ppPreExponential->XmlReadValue("stepsize", false);
      if (pLowertxt && pUppertxt){
        double valueL(0.0), valueU(0.0), stepsize(0.0);
        stringstream s3(pLowertxt), s4(pUppertxt), s5(pStepStxt); s3 >> valueL; s4 >> valueU; s5 >> stepsize;
        set_PreExp(valueL, valueU, stepsize);
      }
      else{
        set_PreExp(value);
      }
    }

    const char* pNInftxt = ppReac->XmlReadValue("me:nInfinity", false);
    if (pNInftxt)
    {
      PersistPtr ppNInf = ppReac->XmlMoveTo("me:nInfinity") ;
      double value = 0.0;
      stringstream s2(pNInftxt); s2 >> value ;
      const char* pLowertxt = ppNInf->XmlReadValue("lower", false);
      const char* pUppertxt = ppNInf->XmlReadValue("upper", false);
      const char* pStepStxt = ppNInf->XmlReadValue("stepsize", false);
      if (pLowertxt && pUppertxt){
        double valueL(0.0), valueU(0.0), stepsize(0.0);
        stringstream s3(pLowertxt), s4(pUppertxt), s5(pStepStxt); s3 >> valueL; s4 >> valueU; s5 >> stepsize;
        set_NInf(valueL, valueU, stepsize);
      }
      else{
        set_NInf(value);
      }
    }

    const char* pERConctxt   = ppReac->XmlReadValue("me:excessReactantConc",false);
    if (pERConctxt)
    {
      stringstream s3(pERConctxt);
      double erconc = 0.0;
      s3 >> erconc;
      m_srct->setExcessReactantConc(erconc);
    }

    // Determine the method of MC rate coefficient calculation.
    const char* pMCRCMethodtxt = ppReac->XmlReadValue("me:MCRCMethod") ;
    if(pMCRCMethodtxt)
    {
      m_pMicroRateCalculator = MicroRateCalculator::Find(pMCRCMethodtxt);
      if(!m_pMicroRateCalculator)
      {
        cerr << "Unknown method " << pMCRCMethodtxt
          << " for the determination of Microcanonical rate coefficients in reaction "
          << getName();
        return false;
      }
    }

    // Determine the method of estimating tunneling effect.
    const char* pTunnelingtxt = ppReac->XmlReadValue("me:tunneling") ;
    if(pTunnelingtxt)
    {
      m_pTunnelingCalculator = TunnelingCalculator::Find(pTunnelingtxt);
      if(!m_pTunnelingCalculator)
      {
        cerr << "Unknown method " << pTunnelingtxt
          << " for the determination of tunneling coefficients in reaction "
          << getName();
        return false;
      }
    }
    else{
      cinfo << "No tunneling method was found for " << getName() << endl;
    }

    return true ;
  }

  //
  // Calculate grained forward and reverse k(E)s from trainsition state flux
  //
  void AssociationReaction::calcGrainRateCoeffs(){

    vector<double> rctGrainDOS;
    vector<double> pdtGrainDOS;
    m_srct->getGrainDensityOfStates(rctGrainDOS) ;
    m_pdt1->getGrainDensityOfStates(pdtGrainDOS) ;

    const int TSFluxGrainZPE  = getTSFluxGrnZPE();
    const int rctGrainZPE = m_srct->get_grnZpe();
    const int pdtGrainZPE = m_pdt1->get_grnZpe();

    const int MaximumGrain = getEnv().MaxGrn;
    m_GrainKfmc.clear();
    m_GrainKfmc.resize(MaximumGrain , 0.0);
    m_GrainKbmc.clear();
    m_GrainKbmc.resize(MaximumGrain , 0.0);

    // For AssociationReaction, TSFlux is calculated from ILT
    for (int i = TSFluxGrainZPE - pdtGrainZPE, j = 0; i < MaximumGrain; ++i, ++j){
      m_GrainKbmc[i] = m_GrainTSFlux[j] / pdtGrainDOS[i];
    }
    for (int i = TSFluxGrainZPE - rctGrainZPE, j = 0; i < MaximumGrain; ++i, ++j){
      m_GrainKfmc[i] = m_GrainTSFlux[j] / rctGrainDOS[i];
    }

    // the code that follows is for printing of the f & r k(E)s
    if (getEnv().kfEGrainsEnabled){
      ctest << "\nk_f(e) grains for " << getName() << ":\n{\n";
      for (int i = 0; i < MaximumGrain; ++i){
        ctest << m_GrainKfmc[i] << endl;
      }
      ctest << "}\n";
    }
    if (getEnv().kbEGrainsEnabled){
      ctest << "\nk_b(e) grains for " << getName() << ":\n{\n";
      for (int i = 0; i < MaximumGrain; ++i){
        ctest << m_GrainKbmc[i] << endl;
      }
      ctest << "}\n";
    }
    if (getEnv().testRateConstantEnabled)
      testRateConstant();
  }

  //  // Test k(T)
  //  void AssociationReaction::testRateConstant() {
  //    vector<double> rctGrainDOS;
  //    vector<double> rctGrainEne;
  //    m_srct->getGrainDensityOfStates(rctGrainDOS) ;
  //    m_srct->getGrainEnergies(rctGrainEne);
  //
  //    const int MaximumGrain = getEnv().MaxGrn;
  //    double k_inf = 0.0;
  //    const double beta = getEnv().beta;
  //    for (int i = 0; i < MaximumGrain; ++i){
  //      k_inf += m_GrainKfmc[i] * exp( log(rctGrainDOS[i]) - beta * rctGrainEne[i] ) ;
  //    }
  //    const double prtfn = canonicalPartitionFunction(rctGrainDOS, rctGrainEne, beta);
  //    const double trans = translationalContribution(m_rct1->getMass(), m_rct2->getMass(), beta);
  //    k_inf /= prtfn;
  //    k_inf /= trans;
  //    const double temperature = 1. / (boltzmann_RCpK * beta);
  //    ctest << "Association rate constant of " << getName() << ": k(" << temperature << ") = " << k_inf << endl;
  //  }

  // Test k(T)
  void AssociationReaction::testRateConstant() {
    vector<double> pdtGrainDOS;
    vector<double> pdtGrainEne;
    m_pdt1->getGrainDensityOfStates(pdtGrainDOS) ;
    m_pdt1->getGrainEnergies(pdtGrainEne);

    const int MaximumGrain = getEnv().MaxGrn;
    double k_inf = 0.0;
    const double beta = getEnv().beta;
    for (int i = 0; i < MaximumGrain; ++i){
      k_inf += m_GrainKbmc[i] * exp( log(pdtGrainDOS[i]) - beta * pdtGrainEne[i] ) ;
    }
    const double prtfn = canonicalPartitionFunction(pdtGrainDOS, pdtGrainEne, beta);
    k_inf /= prtfn;
    double Keq = calcEquilibriumConstant();
    k_inf *= Keq;
    const double temperature = 1. / (boltzmann_RCpK * beta);
    ctest << "Association rate constant of " << getName() << ": k_inf(" << temperature << ") = " << k_inf << endl;
  }

}//namespace
