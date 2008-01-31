//
// ModelledMolecule.cpp
//
// Author: Struan Robertson
//-------------------------------------------------------------------------------------------
#include "Molecule.h"

using namespace std ;
using namespace Constants ;

namespace mesmer
{

  //
  //Constructor
  //
  ModelledMolecule::ModelledMolecule(const MesmerEnv& Env): Molecule(Env),
    m_RotCstA(0.0),
    m_RotCstB(0.0),
    m_RotCstC(0.0),
    m_Sym(1.0),
    m_ZPE(0.0),
    m_SpinMultiplicity(1),
    m_grnZpe(0),
    m_pDensityOfStatesCalculator(NULL),
    m_RC_chk(-1),
    m_Sym_chk(-1),
    m_ZPE_chk(-1),
    m_SpinMultiplicity_chk(-1),
    m_VibFreq_chk(-1),
    m_eleExc(),
    m_VibFreq(),
    m_cellEne(),
    m_cellDOS(),
    m_grainEne(),
    m_grainDOS()
  {}

  ModelledMolecule::~ModelledMolecule()
  {
    if (m_RC_chk == 0) cinfo << "Rotational constants are provided but not used in " << getName() << endl;
    if (m_Sym_chk == 0) cinfo << "m_Sym is provided but not used in " << getName() << endl;
    if (m_ZPE_chk == 0) cinfo << "m_ZPE is provided but not used in " << getName() << endl;
    if (m_SpinMultiplicity_chk == 0) cinfo << "m_SpinMultiplicity is provided but not used in " << getName() << endl;
    if (m_VibFreq_chk == 0) cinfo << "m_VibFreq is provided but not used in " << getName() << endl;

    // Free any memory assigned for calculating densities of states.
    if (m_grainDOS.size()) m_grainDOS.clear();
    if (m_grainEne.size()) m_grainEne.clear();
    if (m_cellDOS.size()) m_cellDOS.clear();
    if (m_cellEne.size()) m_cellEne.clear();
    if (m_VibFreq.size()) m_VibFreq.clear();
  }

  //
  //Initialization
  //
  bool ModelledMolecule::InitializeMolecule(PersistPtr pp)
  {
    //Read base class parameters first
    PersistPtr oldpp = pp;

    if(!Molecule::InitializeMolecule(pp)){
      stringstream errorMsg;
      errorMsg << "InitializeMolecule for " << getName() << " before constructing ModelledMolecule with errors.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
    }

    pp = oldpp;

    PersistPtr ppPropList = pp->XmlMoveTo("propertyList");
    if(!ppPropList)
        ppPropList=pp; //Be forgiving; we can get by without a propertyList element

    const char* txt;

    bool hasVibFreq = true; bool hasRotConst = true;
    txt= ppPropList->XmlReadProperty("me:vibFreqs");
    if(!txt){
      hasVibFreq = false;
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:vibFreqs. Maybe an atom or atomic ion.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
      m_VibFreq_chk = -1;
      //setFlag(true); // it maybe an atom so not necessary to set this flag. Just produce warning.
    }
    else { istringstream idata(txt); double x; while (idata >> x) m_VibFreq.push_back(x); m_VibFreq_chk = 0;}

    txt= ppPropList->XmlReadProperty("me:rotConsts");
    if(!txt){
      hasRotConst = false;
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:rotConsts. Maybe an atom or atomic ion.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
      m_RC_chk = -1;
      //setFlag(true); // it maybe an atom so not necessary to set this flag. Just produce warning.
    }
    else {
      istringstream idata(txt);
      std::vector<double> rCnst(3);
      idata >> rCnst[0]
            >> rCnst[1]
            >> rCnst[2];
      rCnst[0] = abs(rCnst[0]);
      rCnst[1] = abs(rCnst[1]);
      rCnst[2] = abs(rCnst[2]);
      std::sort(rCnst.begin(), rCnst.end());
      m_RotCstA = rCnst[2];
      m_RotCstB = rCnst[1];
      m_RotCstC = rCnst[0];
      m_RC_chk = 0;
    }

    if (hasVibFreq != hasRotConst){
      stringstream errorMsg;
      errorMsg << getName()
      << " has improper setting on vibrational frequencies or rotational constants. Check input file to remove this error.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      setFlag(true);
    }

    txt= ppPropList->XmlReadProperty("me:eletronicExcitation");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:eletronicExcitation for " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
    }
    else {
      istringstream idata(txt); double _iele = 0.; m_eleExc.clear();
      while (idata >> _iele) m_eleExc.push_back(_iele);
    }

    txt= ppPropList->XmlReadProperty("me:symmetryNumber");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:symmetryNumber. Default value " << m_Sym << " is used.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
      m_Sym_chk = -1;
      //setFlag(true);
    }
    else { istringstream idata(txt); idata >> m_Sym; m_Sym_chk = 0;}

    txt= ppPropList->XmlReadProperty("me:ZPE");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:ZPE";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      m_ZPE_chk = -1;
    }
    else { istringstream idata(txt); idata >> m_ZPE ; m_ZPE_chk = 0;}

    // Determine the method of DOS calculation.
    const char* pDOSCMethodtxt = pp->XmlReadValue("me:DOSCMethod", false) ;
    if(pDOSCMethodtxt)
    {
      m_pDensityOfStatesCalculator = DensityOfStatesCalculator::Find(pDOSCMethodtxt);
      if(!m_pDensityOfStatesCalculator) // if the provided method cannot be found,
      {
        stringstream errorMsg;
        errorMsg << "Unknown method " << pDOSCMethodtxt
          << " for the calculation of DOS in " << getName()
          << ". Please check spelling error. Default method <Classical rotors> is used.";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
        pDOSCMethodtxt = "Classical rotors";
        m_pDensityOfStatesCalculator = DensityOfStatesCalculator::Find(pDOSCMethodtxt);
      }
    }
    else{ // if no method is provided.
        stringstream errorMsg;
        errorMsg << "No method for the calculation of DOS in " << getName()
          << " is provided. Default method <Classical rotors> is used.";
        meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      pDOSCMethodtxt = "Classical rotors"; // must exist
      m_pDensityOfStatesCalculator = DensityOfStatesCalculator::Find(pDOSCMethodtxt);
    }

    txt= ppPropList->XmlReadProperty("me:spinMultiplicity");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:spinMultiplicity in " << getName()
               << ". Default value "<< m_SpinMultiplicity << " is used.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
    }
    else
    {
      istringstream idata(txt);
      idata >> m_SpinMultiplicity;
      m_SpinMultiplicity_chk = 0;
    }

    if (getFlag()){
      stringstream errorMsg;
      errorMsg << "Error(s) while initializing: " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      return false;
    }

    return true;
  }

  //
  // Get cell density of states.
  //
  void ModelledMolecule::getCellDensityOfStates(vector<double> &cellDOS) {
    // If density of states have not already been calcualted then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;
    cellDOS = m_cellDOS;
  }

  //
  // Get cell energies.
  //
  void ModelledMolecule::getCellEnergies(vector<double> &CellEne) {
    // If density of states have not already been calcualted then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;
    CellEne = m_cellEne;
  }

  //
  // Get grain density of states.
  //
  void ModelledMolecule::grnDensityOfStates(vector<double> &grainDOS) {
    // If density of states have not already been calcualted then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;
    grainDOS = m_grainDOS;
  }

  //
  // Get grain energies.
  //
  void ModelledMolecule::grnEnergies(vector<double> &grainEne) {
    // If density of states have not already been calcualted then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;
    grainEne = m_grainEne;
  }

  //
  // Get Grain Boltzmann distribution.
  //
  void ModelledMolecule::grnBoltzDist(vector<double> &grainBoltzDist)
  {
    // If density of states have not already been calcualted then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;

    int MaximumGrain = getEnv().MaxGrn ;
    double beta = getEnv().beta;

    grainBoltzDist.resize(MaximumGrain, 0.0);
    // Calculate the Boltzmann distribution.
    // Note the extra 10.0 is to prevent underflow, it is removed during normalization.

    double prtfn(0.0) ;
    for (int i = 0; i < MaximumGrain; ++i) {
        double tmp = log(m_grainDOS[i]) - beta*m_grainEne[i] + 10.0 ;
        tmp = exp(tmp) ;
        prtfn += tmp ;
        grainBoltzDist[i] = tmp ;
    }

    // Normalize the Boltzmann distribution.

    for (int i = 0; i < MaximumGrain; ++i) {
        grainBoltzDist[i] /= prtfn ;
    }

    if (getEnv().grainBoltzmannEnabled){
      ctest << "\nTest grain Boltzmann distribution:\n{\n";
      for (int i = 0; i < MaximumGrain; ++i){
        ctest << sqrt(grainBoltzDist[i]) << endl;
      }
      ctest << "}\n";
    }
  }

    //
    // Get Electronic excitations
    //
    void ModelledMolecule::getEleExcitation(vector<double> &elecExci){
      elecExci.clear();
      for (vector<double>::size_type i = 0; i < m_eleExc.size(); ++i){
        elecExci.push_back(m_eleExc[i]);
      }
    }


  //
  // Get Grain canonical partition function.
  //
  double ModelledMolecule::grnCanPrtnFn() {
    // If density of states have not already been calculated then do so.
    if (!m_cellDOS.size())
      calcDensityOfStates() ;

    double CanPrtnFn(0.0) ;

    // Calculate the ro-vibrational partition function based on the grain
    // densities of states, and not the molecular properties, for consistency.

    const int MaximumGrain = getEnv().MaxGrn ;
    const double beta = getEnv().beta;

    for (int i = 0; i < MaximumGrain; ++i) {
		if (m_grainDOS[i] > 0.0) 
			CanPrtnFn += exp( log(m_grainDOS[i]) - beta*m_grainEne[i] ) ;
    }

	  // The following catches the case where the molecule is a single atom

	  CanPrtnFn = max(CanPrtnFn, 1.0) ;

    // Electronic partition function.
    CanPrtnFn *= double(getSpinMultiplicity()) ;

    if (1){stringstream errorMsg;
    errorMsg << "CanPrtnFn = " << CanPrtnFn << ", molecular name: " << getName();
    meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);}

    // Translational partition function.
    return CanPrtnFn ;
  }

  int ModelledMolecule::test_rotConsts()
  {
    std::vector<double> mmtsInt;
    return get_rotConsts(mmtsInt);
  }

  int ModelledMolecule::get_rotConsts(std::vector<double> &mmtsInt)
  {
    //if (m_RC_chk = -1){ // replace the line below by this line _2007_12_07__16_01_51_ you will encounter a problem somewhere else
    if (m_RC_chk == -1){
      {stringstream errorMsg;
      errorMsg << "Rotational constants were not defined but requested in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);}
      --m_RC_chk;
      return -4; // treat as a non-rotor
    }
    else if (m_RC_chk < -1){
      --m_RC_chk;
      return -4;
    }
    mmtsInt.clear();
    mmtsInt.push_back(m_RotCstA);
    mmtsInt.push_back(m_RotCstB);
    mmtsInt.push_back(m_RotCstC);
    /* now the classification of rotors is simplified to only three following types. 3-D rotors may have other
    attributes different from one another but in ILT they are treated as the same type. The function return values
    are temporary shorthand representations. */
    ++m_RC_chk;
    if      ((mmtsInt[0] + mmtsInt[1] + mmtsInt[2]) == 0.) return -4; // not a rotor
    else if ((mmtsInt[0] * mmtsInt[1] * mmtsInt[2]) == 0.) return  0; // 2-D linear
    else                                                   return  2; // 3-D symmetric/asymmetric/spherical top
  }

  //
  // Calculate the rovibrational density of states.
  //
  bool ModelledMolecule::calcDensityOfStates()
  {
    if (!get_DensityOfStatesCalculator()->countCellDOS(this)){
      return false;
    }
    calcGrainAverages(); testDensityOfStates() ;
    return true;
  }

  //
  // Test the rovibrational density of states for ModelledMolecule.
  //
  void ModelledMolecule::testDensityOfStates()
  {
    if (getEnv().testDOSEnabled) ctest << endl << "Test density of states for: " << getName() << endl << endl ;
    int MaximumGrain = getEnv().MaxGrn;
    int MaximumCell  = getEnv().MaxCell;

    string comment("Partition function calculation at various temperatures. qtot : partition function as a product of quantum mechanical partition functions for vibrations (1-D harmonic oscillator) and classifical partition functions for rotations.  sumc : (user calculated) cell based partition function. sumg : (user calculated) grain based partition function ");

    PersistPtr ppList = getPersistentPointer()->XmlWriteMainElement("me:densityOfStatesList", comment );

    if (getEnv().testDOSEnabled) ctest << "      T           qtot           sumc           sumg\n";

    //loop through predefined test temperatures
    for ( int n = 0 ; n < 29 ; ++n ) {
      double temp = 100.0*static_cast<double>(n + 2) ;
      double beta = 1.0/(boltzmann_RCpK*temp) ;

      // Calculate partition functions based on cells.

      double sumc  = 0.0 ;
      for ( int i = 0 ; i < MaximumCell ; ++i ) {
        sumc += m_cellDOS[i]*exp(-beta*m_cellEne[i]) ;
      }

      // Calculate partition functions based on grains.

      double sumg  = 0.0 ;
      for ( int i = 0 ; i < MaximumGrain ; ++i ) {
        sumg += m_grainDOS[i]*exp(-beta*m_grainEne[i]) ;
      }

      // Calculate partition functions using analytical formula (treat vibrations classically).

      double qtot = 1.0 ;

      vector<double> rotConst; int rotorType;

      if (!dynamic_cast<SuperMolecule *>(this)) {
        rotorType = get_rotConsts(rotConst);
      }
      else{rotorType = -4;}

      vector<double> vibFreq; get_VibFreq(vibFreq);

      switch(rotorType){
        case 2://3-D symmetric/asymmetric/spherical top
          for ( vector<double>::size_type j = 0 ; j < vibFreq.size() ; ++j ) {
            qtot /= (1.0 - exp(-beta*vibFreq[j])) ;
          }
          qtot *= (sqrt(M_PI/(rotConst[0] * rotConst[1] * rotConst[2]))*(pow(beta,-1.5))/get_Sym()) ;
          break;
        case 0://2-D linear
          for ( vector<double>::size_type j = 0 ; j < vibFreq.size() ; ++j ) {
            qtot /= (1.0 - exp(-beta*vibFreq[j])) ;
          }
          qtot *= (rotConst[0] / (get_Sym()*beta)) ;
          break;
        default:
          qtot = 0.;
      }
      if (getEnv().testDOSEnabled) formatFloat(ctest, temp,  6,  7) ;
      if (getEnv().testDOSEnabled) formatFloat(ctest, qtot,  6, 15) ;
      if (getEnv().testDOSEnabled) formatFloat(ctest, sumc,  6, 15) ;
      if (getEnv().testDOSEnabled) formatFloat(ctest, sumg,  6, 15) ;
      if (getEnv().testDOSEnabled) ctest << endl ;

      //Add to XML document
      PersistPtr ppItem = ppList->XmlWriteElement("me:densityOfStates");
      ppItem->XmlWriteValueElement("me:T",    temp, 6);
      ppItem->XmlWriteValueElement("me:qtot", qtot, 6);
      ppItem->XmlWriteValueElement("me:sumc", sumc, 6);
      ppItem->XmlWriteValueElement("me:sumg", sumg, 6);
    }
    if (getEnv().cellDOSEnabled){
      ctest << endl << "Cell density of states of " << getName() << endl << "{" << endl;
      for (int i = 0; i < MaximumCell; ++i){
        formatFloat(ctest, m_cellEne[i],  6,  15) ;
        formatFloat(ctest, m_cellDOS[i],  6,  15) ;
        ctest << endl ;
      }
      ctest << "}" << endl;
    }

    if (getEnv().grainDOSEnabled){
      ctest << endl << "Grain density of states of " << getName() << endl << "{" << endl;
      for (int i = 0; i < MaximumGrain; ++i){
        formatFloat(ctest, m_grainEne[i],  6,  15) ;
        formatFloat(ctest, m_grainDOS[i],  6,  15) ;
        ctest << endl ;
      }
      ctest << "}" << endl;
    }
  }

  //
  // Calculate the average grain energy and then number of states per grain.
  //
  void ModelledMolecule::calcGrainAverages()
  {
    int MaximumGrain = getEnv().MaxGrn;
    m_grainEne.resize(MaximumGrain, 0.) ;
    m_grainDOS.resize(MaximumGrain, 0.) ;

    //    int igsz = MAXCELL/MAXGRN ;

    // Check that there are enough cells.

    if (getEnv().GrainSize < 1) {
      stringstream errorMsg;
      errorMsg << "The number of Cells is insufficient to produce requested number of Grains.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      exit(1) ;
    }

    int idx1 = 0 ;
    int idx2 = 0 ;
    int grainsize = static_cast<int>(getEnv().GrainSize);
    for (int i = 0 ; i < MaximumGrain ; ++i ) {

      int idx3 = idx1 ;

      // Calculate the number of states in a grain.
      double gNOS = 0.0 ;
      for (int j = 0 ; j < grainsize ; ++j, ++idx1 ){
        gNOS += m_cellDOS[idx1] ;
      }

      // Calculate average energy of the grain if it contains sum states.
      if ( gNOS > 0.0 ) {
        double gSE = 0.0 ; // grain sum of state energy
        for (int j = 0 ; j < grainsize ; ++j, ++idx3 ){
          gSE += m_cellEne[idx3] * m_cellDOS[idx3] ;
        }
        m_grainDOS[idx2] = gNOS ;
        m_grainEne[idx2] = gSE/gNOS ;
      }

      idx2++ ;
    }

    // Issue warning if number of grains produced is less that requested.

    if ( idx2 != MaximumGrain ) {
      stringstream errorMsg;
      errorMsg << "Number of grains produced is not equal to that requested" << endl
               << "Number of grains requested: " << MaximumGrain << endl
               << "Number of grains produced : " << idx2 << " in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
    }
    else{
//      stringstream errorMsg;
//      errorMsg << "Number of grains requested: " << MaximumGrain << endl
//               << "Number of grains produced : " << idx2 << " in " << getName();
//      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
    }

  }

  double ModelledMolecule::get_zpe() {
    if (m_ZPE_chk == -1){
      stringstream errorMsg;
      errorMsg << "m_ZPE was not defined but requested in " << getName() << ". Default value " << m_ZPE << " is given.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      --m_ZPE_chk;
      return m_ZPE;
    }
    else if (m_ZPE_chk < -1){
      --m_ZPE_chk;
      return m_ZPE;
    }
    ++m_ZPE_chk;
    return m_ZPE ;
  }

  void ModelledMolecule::set_zpe(double value) {
    m_ZPE = value;
    ++m_ZPE_chk;
  }

  double ModelledMolecule::get_Sym(void){
    if (m_Sym_chk == -1){
      stringstream errorMsg;
      errorMsg << "m_Sym was not defined but requested in " << getName() << ". Default value " << m_Sym << " is given.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      --m_Sym_chk;
      return m_Sym;
    }
    else if (m_Sym_chk < -1){
      --m_Sym_chk;
      return m_Sym;
    }
    ++m_Sym_chk;
    return m_Sym ;
  }

  void ModelledMolecule::set_grnZpe(int grnZpe) {
    m_grnZpe = grnZpe;
  }

  const int ModelledMolecule::get_grnZpe(){
    return m_grnZpe;
  }

  void ModelledMolecule::get_VibFreq(std::vector<double>& vibFreq){
    if (m_VibFreq_chk >=0){
      vibFreq = m_VibFreq;
      ++m_VibFreq_chk;
    }
  }

  void ModelledMolecule::set_VibFreq(std::vector<double>& vibFreq, bool addition){
    if (addition){
      for (std::vector<double>::size_type i = 0; i < vibFreq.size(); ++i) m_VibFreq.push_back(vibFreq[i]);
    }
    else{
      m_VibFreq = vibFreq;
    }
  }

  int ModelledMolecule::getSpinMultiplicity(){
    if (m_SpinMultiplicity_chk >= 0){
      ++m_SpinMultiplicity_chk;
      return m_SpinMultiplicity ;
    }
    else{
      stringstream errorMsg;
      errorMsg << "m_SpinMultiplicity was not defined but requested in " << getName() << ". Default value " << m_SpinMultiplicity << " is given.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      return m_SpinMultiplicity;
    }
  }

  void   ModelledMolecule::setSpinMultiplicity(int value){
    m_SpinMultiplicity = value;
  }

  void ModelledMolecule::set_DensityOfStatesCalculator(DensityOfStatesCalculator* value){
    m_pDensityOfStatesCalculator = value;
  }

  DensityOfStatesCalculator* ModelledMolecule::get_DensityOfStatesCalculator(){
    return m_pDensityOfStatesCalculator;
  }


}//namespace

