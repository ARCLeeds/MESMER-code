//-------------------------------------------------------------------------------------------
//
// Reaction.cpp
//
// Author: Struan Robertson
// Date:   23/Feb/2003
//
// This file contains the implementation of the Reaction class.
//
//-------------------------------------------------------------------------------------------
#include <limits>
#include "Reaction.h"

using namespace Constants ;
using namespace std;
using namespace mesmer;

namespace mesmer
{
  Reaction::Reaction(MoleculeManager *pMoleculeManager, const MesmerEnv& Env):
    m_Env(Env),
    m_Name(),
    m_pMoleculeManager(pMoleculeManager),
    m_srct(NULL),
    m_rct1(NULL),
    m_rct2(NULL),
    m_pdt1(NULL),
    m_pdt2(NULL),
    m_TransitionState(NULL),
    m_reactiontype(ERROR_REACTION),
    m_HeatOfReaction(0.0),
    m_kfwd(0.0),
    m_CellKfmc(),
    m_GrainKfmc(),
    m_ActEne(0.0),
    m_PreExp(0.0),
    m_NInf(0.0),
    m_ppPersist(),
    m_pMicroRateCalculator(NULL)
  {}

  Reaction::~Reaction(){}

  /*
  Reaction::Reaction(const Reaction& reaction) {
  // Copy constructor - define later SHR 23/Feb/2003
  }

  Reaction& Reaction::operator=(const Reaction& reaction) {
  // Assignment operator - define later SHR 23/Feb/2003

  return *this ;
  }
  */

  //
  // Read the Molecular data from inout stream.
  //
  bool Reaction::InitializeReaction(PersistPtr ppReac)
  {
    m_ppPersist = ppReac;

    //Read reaction ID
    const char* id = ppReac->XmlReadValue("id");
    if(id) m_Name = id; //Continues if reaction id not found
    else{
      {stringstream errorMsg;
      errorMsg << "Reaction ID not found\n";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
    }

    Molecule* pMol1(NULL) ;
    Molecule* pMol2(NULL) ;

    //Read reactants
    PersistPtr ppReactant1  = ppReac->XmlMoveTo("reactant");
    pMol1 = GetMolRef(ppReactant1);
    if(!pMol1) return false;
    PersistPtr ppReactant2  = ppReactant1->XmlMoveTo("reactant");
    if(ppReactant2)
    {
      pMol2 = GetMolRef(ppReactant2);
      if(!pMol2){
        {stringstream errorMsg;
        errorMsg << "Reactant 2 defined in Reaction " << getName() << " is incomplete.";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);}
        return false;
      }
    }

    //Put the CollidingMolecule into m_rct1, even if it is second in datafile
    CollidingMolecule* pColMol = dynamic_cast<CollidingMolecule*>(pMol1);
    if(pColMol){
      m_rct1 = pColMol;
      m_rct2 = dynamic_cast<ModelledMolecule*>(pMol2);
    }
    else{
      pColMol = dynamic_cast<CollidingMolecule*>(pMol2);
      if(!pColMol){
        {stringstream errorMsg;
        errorMsg << "At least one of the reactants has to be a colliding molecule";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);}
        return false;
      }
      m_rct1 = pColMol;
      m_rct2 = dynamic_cast<ModelledMolecule*>(pMol1);
    }

    if (m_rct1 && m_rct2){ // the reactant side has two molecules
      {stringstream errorMsg;
      errorMsg << "Reaction " << m_Name << " has two reactants. ";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}

      // check whether there is any SuperMolecule in m_molmap contains pMol1 & pMol2
      string id; //shoud not set any name for it.
      SuperMolecule* pSupMol = NULL;
      while(m_pMoleculeManager->GetNextMolecule(id, pSupMol)){ // get next SuperMolecule
        // if found a SuperMolecule
        ModelledMolecule*  rm1 = pSupMol->getMember1();
        ModelledMolecule*  rm2 = pSupMol->getMember2();
        if (!rm1 && !rm2){// there is no data inside, occupy it!
          pSupMol->setMembers(m_rct1, m_rct2);
          m_srct = pSupMol;
          {stringstream errorMsg;
          errorMsg << "Set members of the SuperMolecule: " << m_srct->getName();
          meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
          break;
        }
      }
      if (!pSupMol){
        {stringstream errorMsg;
        errorMsg << "No SuperMolecule was found.";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
        // there will always at least one SuperMolecule in m_molmap, check the end of addmol() in MoleculeManager.cpp.
        /* need to create one (mark _2007_12_10__17_10_18_)
        write a SuperMolecule creator that acquire a position in the XML
        */
      }
    }
    else{
        {stringstream errorMsg;
        errorMsg << "Reaction " << m_Name << " has only one reactant";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
    }

    //Read products ... if any.
    pMol1=NULL; pMol2=NULL;
    PersistPtr ppProduct1 = ppReac->XmlMoveTo("product");
    if (ppProduct1) {
      pMol1 = GetMolRef(ppProduct1);

      PersistPtr ppProduct2  = ppProduct1->XmlMoveTo("product");
      pMol2 = GetMolRef(ppProduct2);

      //Put the Colliding Molecule into m_pdt1, even if it is second in datafile
      pColMol = dynamic_cast<CollidingMolecule*>(pMol1);
      if(pColMol)
      {
        m_pdt1 = static_cast<ModelledMolecule*>(pColMol);
        m_pdt2 = dynamic_cast<ModelledMolecule*>(pMol2);
      }
      else
      {
        pColMol = dynamic_cast<CollidingMolecule*>(pMol2);
        if(!pColMol) { // both products are not CollidingMolecule -> dissociation reaction
          m_pdt1 = dynamic_cast<ModelledMolecule*>(pMol1);
          m_pdt2 = dynamic_cast<ModelledMolecule*>(pMol2); // do we need to check the existence of m_pdt2 ?
        }
        m_pdt1 = static_cast<ModelledMolecule*>(pColMol);
        m_pdt2 = dynamic_cast<ModelledMolecule*>(pMol1);
      }
    }

    // Read the transition state (if present)
    PersistPtr ppTransitionState = ppReac->XmlMoveTo("me:transitionState") ;
    if (ppTransitionState)
    {
      TransitionState* pTrans = dynamic_cast<TransitionState*>(GetMolRef(ppTransitionState));
      if(pTrans) m_TransitionState = pTrans;

      /* It would be better to use the ZPEs rather than threshold
      if(m_TransitionState)
      {
      const char* pthreshtxt = ppReac->XmlReadValue("me:threshold",false);
      if(pthreshtxt)
      {
      stringstream ss(pthreshtxt);
      ss >> m_E0;
      }
      */
    }

    // Read the heat of reaction (if present).
    const char* pHeatRxntxt = ppReac->XmlReadValue("me:HeatOfReaction",false);
    if (pHeatRxntxt){
      stringstream s1(pHeatRxntxt);
      s1 >> m_HeatOfReaction ;
    }
    else{ // calculate HeatOfReaction
      double zpe_pdt1 = m_pdt1 ? m_pdt1->get_zpe() : 0.;
      double zpe_pdt2 = m_pdt2 ? m_pdt2->get_zpe() : 0.;
      double zpe_rct1 = m_rct1 ? m_rct1->get_zpe() : 0.;
      double zpe_rct2 = m_rct2 ? m_rct2->get_zpe() : 0.;
      m_HeatOfReaction = zpe_pdt1 + zpe_pdt2 - zpe_rct1 - zpe_rct2;
    }

    //Read in Kinetic rate parameters, if present
    m_ActEne = std::numeric_limits<double>::quiet_NaN();//means not set

    const char* pActEnetxt = ppReac->XmlReadValue("me:activationEnergy",false);
    if (pActEnetxt)
    {
      stringstream s1(pActEnetxt); s1 >> m_ActEne ;
    }
    const char* pPreExptxt = ppReac->XmlReadValue("me:preExponential",false);
    if (pPreExptxt)
    {
      stringstream s2(pPreExptxt); s2 >> m_PreExp ;
    }
    const char* pNInftxt   = ppReac->XmlReadValue("me:nInfinity",false);
    if (pNInftxt)
    {
      stringstream s3(pNInftxt); s3 >> m_NInf ;
    }


    // Classify the reaction.

    if (m_rct1 && m_pdt1 && !m_rct2 && !m_pdt2)
      m_reactiontype = ISOMERIZATION ;
    else if (m_rct1 && m_pdt1 && m_rct2 && !m_pdt2)
      m_reactiontype = ASSOCIATION ;
    else if (m_rct1)
      m_reactiontype = DISSOCIATION ;
    else {
      m_reactiontype = ERROR_REACTION ;
      {stringstream errorMsg;
      errorMsg << "Unknown combination of reactants and products";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);}
      return false;
    }

    // Determine the method of MC rate coefficient calculation.
    const char* pMCRCMethodtxt = ppReac->XmlReadValue("me:MCRCMethod") ;
    if(pMCRCMethodtxt)
    {
      m_pMicroRateCalculator = MicroRateCalculator::Find(pMCRCMethodtxt);
      if(!m_pMicroRateCalculator)
      {
        {stringstream errorMsg;
        errorMsg << "Unknown method " << pMCRCMethodtxt
                 << " for the determination of Microcanonical rate coefficients in reaction "
                 << m_Name;
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);}
        return false;
      }
    }


    return true;
  }

  //
  // Locate molecule in molecular map.
  //
  Molecule* Reaction::GetMolRef(PersistPtr pp)
  {
    Molecule* pMol = NULL;
    
    if(!pp) return NULL;
    PersistPtr ppmol = pp->XmlMoveTo("molecule");
    if(!ppmol) return NULL;

    string pRef = ppmol->XmlReadValue("ref");
    if(pRef.size()){ // if got the name of the molecule
      string pType = ppmol->XmlReadValue("me:type");
      if(pType.size()){ // initialize molecule here with the specified type (need to know m_ppIOPtr)
        PersistPtr ppMolList = m_pMoleculeManager->get_PersistPtr();
        if(!ppMolList)
        {
          stringstream errorMsg;
          errorMsg << "No molecules have been specified";
          meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
          return false;
        }
        pMol = m_pMoleculeManager->addmol(pRef, pType, ppMolList, m_Env);
      }
    }


    if(!pMol)
    {
      {stringstream errorMsg;
      errorMsg << "Cannot find molecule: " << pRef;
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
      return NULL;
    }

    return pMol;
  }

  //
  // Returns the unimolecular species in each reaction, i.e. for association
  // (source term) or dissociation (sink term) reaction one species is returned,
  // for an isomerization reaction two species are returned.
  //
  int Reaction::get_unimolecularspecies(vector<ModelledMolecule *> &unimolecularspecies) const
  {
    switch(m_reactiontype) {
    case ISOMERIZATION :
      unimolecularspecies.push_back(m_rct1) ;
      unimolecularspecies.push_back(m_pdt1) ;
      return 3;

    case ASSOCIATION :
      unimolecularspecies.push_back(m_pdt1) ;
      return 2;

    case DISSOCIATION :
      unimolecularspecies.push_back(m_rct1) ;
      return 1;

    default :
      return 0;
    }
    return 0;
  }

  // Returns the bi-molecular speices (reactants) for association reaction.
  SuperMolecule* Reaction::get_bi_molecularspecies(void) const
  {
    switch(m_reactiontype) {
    case ASSOCIATION :
      return m_srct;

    default :
      return NULL;
    }
    return NULL;
  }

  //
  // Get the prinincipal source reactant (i.e. reactant not in excess) if it exists.
  // (Not sure if this is a good idea, may be better to pass a Map in.)
  //
  ModelledMolecule *Reaction::get_pseudoIsomer() const
  {
    ModelledMolecule *pseudoIsomer = NULL ;
    if(m_reactiontype == ASSOCIATION) pseudoIsomer = m_pdt1 ;
    return pseudoIsomer ;
  }

  //
  // Calculate reaction equilibrium constant.
  //
  double Reaction::calcEquilibriumConstant() {

    double Keq(0.0) ;

    // Get Canonical partition functions.

    double Qrct1 = m_rct1->grnCanPrtnFn() ;
    double Qpdt1 = m_pdt1->grnCanPrtnFn() ;

    double Qrct2 = (m_rct2)? m_rct2->grnCanPrtnFn() : 1.0 ;
    double Qpdt2 = (m_pdt2)? m_pdt2->grnCanPrtnFn() : 1.0 ;

    // Calculate the equilibrium constant.
    if(1){stringstream errorMsg;
    errorMsg << "Qrct1 = " << Qrct1 << ", Qpdt1 = " << Qpdt1 << ", Qrct2 = " << Qrct2 << ", Qpdt2 = " << Qpdt2;
    meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}

    double beta = m_Env.beta ;

    Keq = (Qpdt1*Qpdt2)/(Qrct1*Qrct2) ;     // Whatever reaction.
    Keq *= exp(-beta*m_HeatOfReaction) ;

    // check in ASSOCIATION reaction, if the partition function of the SuperMolecule is equal to the product of the
    // partitions of the two reactants.
    if (m_rct1 && m_rct2 && m_pdt1 && !m_pdt2){
      double Qrcts = m_srct->grnCanPrtnFn();
      if (Qrcts != Qrct1){
        double diff = Qrcts - Qrct1;
        stringstream errorMsg;
        errorMsg << "Partition function of the SuperMolecule is not consistent with the product of partition functions of the reactants. Diff = " << diff;
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      }
    }

    return Keq ;
  }

  //
  // Access microcanoincal rate coefficients.
  //
  void Reaction::get_MicroRateCoeffs(std::vector<double> &kmc) {
    calcGrnAvrgMicroRateCoeffs();
    kmc = m_GrainKfmc ;
  }

  //
  // Calculate grain averaged microcanonical rate coefficients.
  //
  bool Reaction::calcGrnAvrgMicroRateCoeffs() {

    // Calculate microcanonical rate coefficients.
    if (m_CellKfmc.size()==0)
    {
      if(!m_pMicroRateCalculator->calculateMicroRateCoeffs(this, m_CellKfmc, m_Env) ||
        (m_Env.microRateEnabled && !m_pMicroRateCalculator->testMicroRateCoeffs(this, m_CellKfmc, m_ppPersist, m_Env)))
        return false;
    }

    // Calculate Grain averages of microcanonical rate coefficients.
    if (m_GrainKfmc.size()==0)
        return grnAvrgMicroRateCoeffs() ;
    return true;
  }

  //
  // Access microcanonical rate coefficients - cell values are averaged
  // to give grain values. This code is similar to that in Molecule.cpp
  // and this averaging should be done there. SHR 19/Sep/2004.
  //
  bool Reaction::grnAvrgMicroRateCoeffs() {

    int MaximumGrain = m_Env.MaxGrn;
    double currentGrainSize = m_Env.GrainSize;
    m_GrainKfmc.resize(MaximumGrain, 0.);

    // Extract density of states of equilibrium molecule.

    vector<double> cellDOS(m_Env.MaxCell,0.0) ;
    m_rct1->getCellDensityOfStates(cellDOS) ;

    // Check that there are enough cells.

    if (currentGrainSize < 1) {
      {stringstream errorMsg;
      errorMsg << "Not enought Cells to produce requested number of Grains.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);}
      exit(1) ;
    }

    int idx1 = 0 ;
    int idx2 = 0 ;

    for (int i = 0; i < MaximumGrain ; ++i ) {

      int idx3 = idx1 ;

      // Calculate the number of states in a grain.

      double gNOS = .0 ;
      for (int j = 0 ; j < currentGrainSize ; ++j, ++idx1 )
        gNOS += cellDOS[idx1] ;

      // Calculate average energy of the grain if it contains sum states.
      // need to think about how to deal with DOS/ENE of atoms. (there should have no rovibrational DOS/ENE for atoms)
      if ( gNOS > 0.0 ) {

        double gSE = .0;
        for (int j= 0 ; j < currentGrainSize ; ++j, ++idx3 )
            gSE += m_CellKfmc[idx3] * cellDOS[idx3] ;

        m_GrainKfmc[idx2] = gSE/gNOS ;
      }
      idx2++ ;
    }

    // Issue warning if number of grains produced is less that requested.
    if ( idx2 != MaximumGrain ) {
      {stringstream errorMsg;
      errorMsg << "Number of grains produced is not equal to that requested" << endl
               << "Number of grains requested: " << MaximumGrain << endl
               << "Number of grains produced : " << idx2 << " in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);}
    }
    else{
//      {stringstream errorMsg;
//      errorMsg << "Number of grains requested: " << MaximumGrain << endl
//               << "Number of grains produced : " << idx2 << " in " << getName();
//      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}
    }
    return true;
  }

  //
  // Add microcanonical terms to collision operator
  //
  void Reaction::AddMicroRates(dMatrix *CollOptr,
      isomerMap &isomermap,
      sourceMap &sourcemap,
      const double rMeanOmega)
  {

    // Calculate Microcanonical rate coefficients.

    calcGrnAvrgMicroRateCoeffs() ;

    // Add microcanonical rates to the collision operator.

    switch(m_reactiontype) {
    case ISOMERIZATION :
      AddIsomerReactionTerms(CollOptr, isomermap, rMeanOmega) ;
      break;

    case ASSOCIATION :
      AddAssocReactionTerms(CollOptr, isomermap, sourcemap, rMeanOmega) ;
      break;

    case DISSOCIATION :
      AddDissocReactionTerms(CollOptr, isomermap, rMeanOmega) ;
      break;

    default :
      stringstream errorMsg;
      errorMsg << "Unknown reaction type";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);

    }
  }

  //
  // Add isomer reaction terms to collision matrix.
  //
  void Reaction::AddIsomerReactionTerms(dMatrix         *CollOptr,
                                        isomerMap       &isomermap,
                                        const double    rMeanOmega)
  {
    // Locate isomers in system matrix.
    const int rctLocation = isomermap[dynamic_cast<CollidingMolecule*>(m_rct1)] ;
    const int pdtLocation = isomermap[dynamic_cast<CollidingMolecule*>(m_pdt1)] ;

    // Get densities of states for detailed balance.
    const int MaximumGrain = m_Env.MaxGrn;
    vector<double> rctDOS(MaximumGrain, 0.0) ;
    vector<double> pdtDOS(MaximumGrain, 0.0) ;

    m_rct1->grnDensityOfStates(rctDOS) ;
    m_pdt1->grnDensityOfStates(pdtDOS) ;

    const int idx = m_pdt1->get_grnZpe() - m_rct1->get_grnZpe() ;
    for ( int i = max(0,-idx) ; i < min(MaximumGrain,(MaximumGrain-idx)) ; ++i ) {
      int ll = i + idx ;
      int ii(rctLocation + ll) ;
      int jj(pdtLocation + i) ;
      (*CollOptr)[ii][ii] -= rMeanOmega * m_GrainKfmc[ll] ;                            // Forward loss reaction.
      (*CollOptr)[jj][jj] -= rMeanOmega * m_GrainKfmc[ll]*rctDOS[ll]/pdtDOS[i] ;       // Backward loss reaction from detailed balance.
      (*CollOptr)[ii][jj]  = rMeanOmega * m_GrainKfmc[ll]*sqrt(rctDOS[ll]/pdtDOS[i]) ; // Reactive gain.
      (*CollOptr)[jj][ii]  = (*CollOptr)[ii][jj] ;                                     // Reactive gain.
    }
  }

  //
  // Add (REVERSIBLE) association reaction terms to collision matrix.
  //
  void Reaction::AddAssocReactionTerms(dMatrix      *CollOptr,
                                       isomerMap    &isomermap,
                                       sourceMap    &sourcemap,
                                       const double rMeanOmega)
  {
    // Locate isomers in system matrix.
    const int pdtLoc  = isomermap[dynamic_cast<CollidingMolecule*>(m_pdt1)] ;
    const int sL      = sourcemap[dynamic_cast<SuperMolecule    *>(m_srct)] ;

    // Get equilibrium constant.
    const double Keq = calcEquilibriumConstant() ;

    // Get Boltzmann distribution for detailed balance.
    const int MaximumGrain = m_Env.MaxGrn ;
    vector<double> srcBoltz(MaximumGrain, 0.0) ;
    m_srct->grnBoltzDist(srcBoltz) ;

    const int colloptrsize = dynamic_cast<CollidingMolecule*>(m_pdt1)->get_colloptrsize() ;

    double DissRateCoeff(0.0) ;

    const int idx = m_pdt1->get_grnZpe() - m_rct1->get_grnZpe() ;
    for ( int i = max(0,-idx) ; i < min(colloptrsize,(colloptrsize-idx)) ; ++i ) {
      int ll = i + idx ;
      int pL(pdtLoc + ll) ;

      (*CollOptr)[pL][pL] -= rMeanOmega * m_GrainKfmc[ll] ;                        // Forward loss reaction.
      (*CollOptr)[pL][sL]  = rMeanOmega * m_GrainKfmc[ll]*sqrt(srcBoltz[ll]/Keq) ; // Reactive gain.
      (*CollOptr)[sL][pL]  = (*CollOptr)[pL][sL] ;                                 // Reactive gain.
      DissRateCoeff       += m_GrainKfmc[ll]*srcBoltz[ll] ;
    }
    (*CollOptr)[sL][sL] -= DissRateCoeff/Keq ;       // Backward loss reaction from detailed balance.

  }

  //
  // Add dissociation reaction terms to collision matrix.
  //
  void Reaction::AddDissocReactionTerms(dMatrix *CollOptr, isomerMap &isomermap, const double rMeanOmega) {

    // Locate reactant in system matrix.
    const int rctLocation = isomermap[dynamic_cast<CollidingMolecule*>(m_rct1)] ;

    for ( int i = 0 ; i < dynamic_cast<CollidingMolecule*>(m_rct1)->get_colloptrsize() ; ++i ) {
        int ii(rctLocation + i) ;
        (*CollOptr)[ii][ii] -= rMeanOmega * m_GrainKfmc[i] ;                            // Forward loss reaction.
    }
  }

}//namespace
