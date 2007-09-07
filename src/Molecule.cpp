//-------------------------------------------------------------------------------------------
//
// Molecule.cpp
//
// Author: Struan Robertson
// Date:   5/Jan/2003
//
// This file contains the implementation of the Molecule class and its derived classes.
//
//-------------------------------------------------------------------------------------------

#include "System.h"

using namespace std ;
using namespace Constants ;
namespace mesmer
{
  Molecule::Molecule():
    m_Mass(0.0),
    m_Sigma(0.0),
    m_Epsilon(0.0)
  {}

  ModelledMolecule::ModelledMolecule():
    m_MmtIntA(0.0),
    m_MmtIntB(0.0),
    m_MmtIntC(0.0),
    m_Sym(0.0),
    m_ZPE(0.0),
    m_cellEne(NULL),
    m_cellDOS(NULL)
  {}

  CollidingMolecule::CollidingMolecule():
    m_egme(NULL),
    m_DeltaEdown(0.0),
    m_ncolloptrsize(0),
    m_collisionFrequency(0.0)
  {}

  ModelledMolecule::~ModelledMolecule()
  {
    // Free any memory assigned for calculating densities of states.
    if (m_cellDOS != NULL) m_alloc.deallocate(m_cellDOS, GetSys()->MAXCell()) ;
    if (m_cellEne != NULL) m_alloc.deallocate(m_cellEne, GetSys()->MAXCell()) ;
  }

  CollidingMolecule::~CollidingMolecule()
  {
    if (m_egme != NULL) delete m_egme ;
  }

  TransitionState::TransitionState()
  {}

  /* Will need Clone() functions
  Molecule::Molecule(const Molecule& molecule) {
  // Copy constructor - define later SHR 23/Feb/2003
  }

  Molecule& Molecule::operator=(const Molecule&) {
  // Assignment operator - define later SHR 23/Feb/2003

  return *this ;
  }
  */

  //
  // Read the Molecular data from I/O stream.
  bool Molecule::InitializeMolecule(System* pSys, PersistPtr p)
  {
    m_pSys = pSys;
    m_ppPersist = p;
    const char* id= m_ppPersist->XmlReadValue("id");
    if(id)
        m_Name = id;
    return !m_Name.empty();
  }

  bool BathGasMolecule::InitializeMolecule(System* pSys, PersistPtr pp)
  {
    //Read base class parameters first
    if(!Molecule::InitializeMolecule(pSys, pp))
        return false;

    PersistPtr ppPropList = pp->XmlMoveTo("propertyList");
    if(!ppPropList)
        ppPropList=pp; //Be forgiving; we can get by without a propertyList element

    const char* txt;

    txt= ppPropList->XmlReadProperty("me:epsilon");
    if(!txt)
        return false;
    { istringstream idata(txt); //extra block ensures idata is initiallised
    idata >> m_Epsilon;
    }

    txt= ppPropList->XmlReadProperty("me:sigma");
    if(!txt)
        return false;
    { istringstream idata(txt);
    idata >> m_Sigma;
    }

    txt= ppPropList->XmlReadProperty("me:MW");
    if(!txt)
        return false;
    { istringstream idata(txt);
    idata >> m_Mass;
    }
    return true;
    //TODO append name of molecule to error message
  }


  bool ModelledMolecule::InitializeMolecule(System* pSys, PersistPtr pp)
  {
    //Read base class parameters first
    if(!Molecule::InitializeMolecule(pSys, pp))
        return false;

    PersistPtr ppPropList = pp->XmlMoveTo("propertyList");
    if(!ppPropList)
        ppPropList=pp; //Be forgiving; we can get by without a propertyList element

    const char* txt;

    txt= ppPropList->XmlReadProperty("me:ZPE");
    if(!txt)
        return false;
    {
        istringstream idata(txt);
        idata >> m_ZPE ;
    }
    txt= ppPropList->XmlReadProperty("me:rotConsts");
    if(!txt)
        return false;
    {
        istringstream idata(txt);
        idata >> m_MmtIntA >> m_MmtIntB >> m_MmtIntC ;
    }
    txt= ppPropList->XmlReadProperty("me:symmetryNumber");
    if(!txt)
        return false;
    {
      istringstream idata(txt);
      idata >> m_Sym;
    }

    txt= ppPropList->XmlReadProperty("me:vibFreqs");
    if(!txt)
        return false;
    {
      istringstream idata(txt);
      double x ;
      while (idata >> x)
          m_VibFreq.push_back(x) ;
    }

    return true;
  }

  bool CollidingMolecule::InitializeMolecule(System* pSys, PersistPtr pp)
  {
    //Read base class parameters first
    if(!ModelledMolecule::InitializeMolecule(pSys, pp))
        return false;

    PersistPtr ppPropList = pp->XmlMoveTo("propertyList");
    if(!ppPropList)
        ppPropList=pp; //Be forgiving; we can get by without a propertyList element

    const char* txt;

    txt= ppPropList->XmlReadProperty("me:epsilon");
    if(!txt)
        return false;
    { istringstream idata(txt); //extra block ensures idata is initiallised
    idata >> m_Epsilon;
    }

    txt= ppPropList->XmlReadProperty("me:sigma");
    if(!txt)
        return false;
    { istringstream idata(txt);
    idata >> m_Sigma;
    }

    txt= ppPropList->XmlReadProperty("me:MW");
    if(!txt)
        return false;
    { istringstream idata(txt);
    idata >> m_Mass;
    }

    txt= ppPropList->XmlReadProperty("me:deltaEDown");
    if(!txt)
        return false;
    { istringstream idata(txt);
    idata >> m_DeltaEdown;
    }

    return true;
  }

  //
  // Get cell density of states.
  //
  void ModelledMolecule::cellDensityOfStates(double *cellDOS) {

    // If density of states have not already been calcualted then do so.

    if (!m_cellDOS)
        calcDensityOfStates() ;

    for (int i = 0 ; i < GetSys()->MAXCell() ; ++i )
        cellDOS[i] = m_cellDOS[i] ;
  }

  //
  // Get cell energies.
  //
  void ModelledMolecule::cellEnergies(double *CellEne) {

    // If energies have not already been calcualted then do so.

    if (!m_cellDOS)
        calcDensityOfStates() ;

    for (int i = 0 ; i < GetSys()->MAXCell() ; ++i )
        CellEne[i] = m_cellEne[i] ;
  }

  //
  // Get grain density of states.
  //
  void ModelledMolecule::grnDensityOfStates(vector<double> &dosGrn) {

    // If density of states have not already been calcualted then do so.

    if (!m_cellDOS)
        calcDensityOfStates() ;

    dosGrn = m_gdos ;
  }

  //
  // Get grain energies.
  //
  void ModelledMolecule::grnEnergies(vector<double> &eGrn) {

    // If energies have not already been calcualted then do so.

    if (!m_cellDOS)
        calcDensityOfStates() ;

    eGrn = m_gdos ;
  }

  //-------------------------------------------------------------------------------------------
  //
  // Methods related to the Master Equation.

  //
  // Initialize the Collision Operator.
  //
  void CollidingMolecule::initCollisionOperator(double beta, double conc, Molecule *pBathGasMolecule) {

    // If density of states have not already been calcualted then do so.

    if (!m_cellDOS)
        calcDensityOfStates() ;

    // Calculate the collision frequency.

    m_collisionFrequency = collisionFrequency(beta, conc, pBathGasMolecule) ;

    // Calculate the collision operator.

    collisionOperator(beta) ;
  }

  //
  // Calculate collision operator
  //
  void CollidingMolecule::collisionOperator(double beta) {

    //
    //     i) Determine Probabilities of Energy Transfer.
    //    ii) Normalisation of Probability matrix.
    //   iii) Symmetrise Collision Matrix.
    //
    int i, j ;

    double alpha = 1.0/m_DeltaEdown ;
    //
    // Allocate memmory.
    //
    if (m_egme)                                 // Delete any existing matrix.
        delete m_egme ;

    m_egme = new dMatrix(GetSys()->MAXGrn()) ;              // Collision operator matrix.

    vector<double> work(GetSys()->MAXGrn(),0.0) ; // Work space.
    //
    // Initialisation and error checking.
    //
    for ( i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
      if (m_gdos[i] <= 0.0) {
        stringstream errorMsg;
        errorMsg << "Data indicates that grain " << i << " of the current colliding molecule has no states.";
        obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
        return ; //***THIS FUNCTION NEEDS AN ERROR RETURN****
      }
    }
    //
    // The collision operator.
    //
    for ( i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
      double ei = m_egrn[i] ;
      double ni = m_gdos[i] ;
      for ( j = i ; j < GetSys()->MAXGrn() ; ++j ) {
        //
        // Transfer to lower Energy -
        //
        (*m_egme)[i][j] = exp(-alpha*(m_egrn[j] - ei)) ;
        //
        // Transfer to higher Energy (via detailed balance) -
        //
        (*m_egme)[j][i] = (*m_egme)[i][j] * (m_gdos[j]/ni)*exp(-beta*(m_egrn[j] - ei)) ;
      }
    }
    //
    // Normalization of Probability matrix.
    // Normalising coefficients are found by using the fact that column sums
    // are unity. The procedure leads to a matrix that is of upper triangular
    // form and the normalisation constants are found by back substitution.
    //
    for ( i = GetSys()->MAXGrn() - 1 ; i > -1 ; --i ) {

      double upperSum(0.0) ;
      for ( j = 0 ; j <= i ; ++j )
          upperSum += (*m_egme)[j][i] ;

      double scaledRemain(0.0) ;
      for ( j = i + 1 ; j < GetSys()->MAXGrn() ; ++j ){
        scaledRemain += (*m_egme)[j][i] * work[j] ;
      }

      if (upperSum <= 0.0) {
        stringstream errorMsg;
        errorMsg << "Normalization coefficients in EGME is smaller than or equal to zero:\n";
        errorMsg << "i = " << i << ", j = " << j;
        obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
        exit(1) ;
      }
      work[i] = (1.0 - scaledRemain) / upperSum ;
    }
    //
    // Apply normalization coefficients and account for collisional
    // loss by subrtacting unity from the leading diagonal.
    //
    cout << endl << "Normalization constants" << endl << endl ;
    for ( i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
      cout <<  m_egrn[i] << " " << work[i] << endl ;
      (*m_egme)[i][i] *= work[i] ;
      (*m_egme)[i][i] -= 1.0 ;
      for ( j = i + 1 ; j < GetSys()->MAXGrn() ; ++j ) {
        (*m_egme)[j][i] *= work[j] ;
        (*m_egme)[i][j] *= work[j] ;
      }
    }

    cout << endl << "Column Sums" << endl << endl ;
    for ( i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
        double columnSum(0.0) ;
        for ( j = 0 ; j < GetSys()->MAXGrn() ; ++j )
            columnSum += (*m_egme)[j][i] ;
        cout << columnSum << endl ;
    }
    //
    // Determine the equilibrium vector for symmetrization. Note the work
    // array is over written and now contains square root of the Boltzman
    // distribution.
    //
    for ( i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
      double ei = log(m_gdos[i]) - beta*m_egrn[i] + 10.0 ;
      ei = exp(ei) ;
      work[i] = sqrt(ei) ;
    }
    //
    // Symmetrization of the collision matrix.
    //
    for ( i = 1 ; i < GetSys()->MAXGrn() ; ++i ) {
      for ( j = 0 ; j < i ; ++j ) {
        (*m_egme)[j][i] *= (work[i]/work[j]) ;
        (*m_egme)[i][j]  = (*m_egme)[j][i] ;
      }
    }
  }
  /*//
  // Diagonalize the Collision Operator. See ReactionManager::diagCollisionOperator()
  //
  void CollidingMolecule::  diagCollisionOperator() {

    // Allocate space for eigenvalues.

    int msize = m_egme->size() ;
    vector<double> rr(msize, 0.0) ;

    m_egme->diagonalize(&rr[0]) ;

    cout << endl ;
    for (int i(0) ; i < msize ; ++i)
        cout << rr[i] << endl;

    cout << endl ;
    for (int i(0) ; i < msize ; ++i)  {
      formatFloat(cout, m_egrn[i],              6, 15) ;
      formatFloat(cout, (*m_egme)[i][pSys->MAXGrn()-1], 6, 15) ;
      formatFloat(cout, (*m_egme)[i][pSys->MAXGrn()-2], 6, 15) ;
      cout << endl ;
    }

  }
  */
  //
  // Calculate collision frequency.
  //
  double CollidingMolecule::collisionFrequency(double beta, double conc, Molecule *pBathGasMolecule) {

    //
    // Lennard-Jones Collision frequency. The collision integral is calculated
    // using the formula of Neufeld et al., J.C.P. Vol. 57, Page 1100 (1972).
    // CONCentration is in molec/cm^3.
    //

    double A = 1.16145 ;
    double B = 0.14874 ;
    double C = 0.52487 ;
    double D = 0.77320 ;
    double E = 2.16178 ;
    double F = 2.43787 ;
    double amu = 1.6606E-27 ;

    double pi = acos(-1.0) ;
    double temp = 1.0/(boltzmann*beta) ;
    //
    // Calculate collision parameter averages.
    //
    double bthMass    = pBathGasMolecule->getMass();
    double bthSigma   = pBathGasMolecule->getSigma();
    double bthEpsilon = pBathGasMolecule->getEpsilon();

    double mu   = amu*m_Mass*bthMass/(m_Mass + bthMass) ;
    double eam  = sqrt(m_Epsilon*bthEpsilon) ;
    double sam  = (m_Sigma + bthSigma)*0.5 ;
    double tstr = temp/eam ;
    //
    // Calculate collision integral.
    //
    double collFrq = A*exp(-log(tstr)*B) + C*exp(-D*tstr) + E*exp(-F*tstr) ;
    //
    // Calculate molecular collision frequency.
    //
    collFrq *= pi*sam*sam*1.e-20*sqrt(8.*1.381e-23*temp/(pi*mu)) ;
    //
    // Calculate overall collision frequency.
    //
    collFrq *= conc*1.e+06 ;

    return collFrq ;
  }

  //
  // Calculate a reaction matrix element.
  //
  double CollidingMolecule::matrixElement(int eigveci, int eigvecj, vector<double> &k, int ndim) {

    double sum = 0.0 ;
    for (int i = 0 ; i < ndim ; ++i)
        sum +=  k[i]*(*m_egme)[i][eigveci]*(*m_egme)[i][eigvecj] ;

    return sum ;
  }

  //
  // Copy collision operator to diagonal block of system matrix.
  //
  void CollidingMolecule::copyCollisionOperator(dMatrix *CollOptr,
                                                const int size,
                                                const int locate,
                                                const double RducdOmega) const
  {

    // Find size of system matrix.

    int smsize = CollOptr->size() ;

    // Check there is enough space in system matrix.

    if (locate + size > smsize) {
      stringstream errorMsg;
      errorMsg << "Error in the size of the system matrix.";
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      exit(1) ;
    }

    // Copy collision operator to the diagonal block indicated by "locate"
    // and multiply by the reduced collision frequencey.

    for (int i(0) ; i < size ; ++i) {
      int ii(locate + i) ;
      for (int j(0) ; j < size ; ++j) {
        int jj(locate + j) ;
        (*CollOptr)[ii][jj] = RducdOmega * (*m_egme)[i][j] ;
      }
    }

  }

  //-------------------------------------------------------------------------------------------
  //
  // Private methods.

  //
  // Calculate the rovibrational density of states.
  //
  void ModelledMolecule::calcDensityOfStates() {

    cout << endl << "The number of Frequencies is " << m_VibFreq.size() << endl ;

    m_cellDOS = m_alloc.allocate(GetSys()->MAXCell()) ;
    m_cellEne = m_alloc.allocate(GetSys()->MAXCell()) ;

    //
    // Initialize density of states array using calculated rotational
    // density of state.
    //

    //From inverse Laplace transform of 3-D asymmetric top rotor(needs revise for varieties)
    double cnt = sqrt(4./(m_MmtIntA * m_MmtIntB * m_MmtIntC))/m_Sym ;

    int i ;
    for ( i = 0 ; i < GetSys()->MAXCell() ; ++i ) {
      m_cellEne[i] = static_cast<double>(i) + 0.5 ;
      m_cellDOS[i] = cnt*sqrt(m_cellEne[i]) ;
    }

    // Implementation of the Bayer-Swinehart algorithm.

    for ( vector<double>::size_type j = 0 ; j < m_VibFreq.size() ; ++j ) {
      int iFreq = static_cast<int>(m_VibFreq[j]) ;
      for ( i = 0 ; i < GetSys()->MAXCell() - iFreq ; ++i )
          m_cellDOS[i + iFreq] += m_cellDOS[i] ;
    }

    // Calculate grain averages.

    calcGrainAverages() ;

    //    if ( get_verbosity() )
    testDensityOfStates() ;

    return ;
  }

  //
  // Test the rovibrational density of states.
  //
  void ModelledMolecule::testDensityOfStates() {

    cout << endl << "Test density of states: " << m_Name << endl << endl ;

    double temp ;
    double beta ;
    double pi = acos(-1.0) ;

    string comment("Partition function calculation at various temperatures.\n qtot : using analytical formula\n sumc : based on cells\n sumg  : based on grains");

    PersistPtr ppList = m_ppPersist->XmlWriteMainElement("me:densityOfStatesList", comment );
    for ( int n = 0 ; n < 29 ; ++n ) {

      temp = 100.0*static_cast<double>(n + 2) ;
      beta = 1.0/(boltzmann*temp) ;

      // Calculate partition functions based on cells.

      double sumc  = 0.0 ;
      for ( int i = 0 ; i < GetSys()->MAXCell() ; ++i ) {
        sumc += m_cellDOS[i]*exp(-beta*m_cellEne[i]) ;
      }

      // Calculate partition functions based on grains.

      double sumg  = 0.0 ;
      for ( int i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {
        sumg += m_gdos[i]*exp(-beta*m_egrn[i]) ;
      }

      // Calculate partition functions using analytical formula.

      double qtot = 1.0 ;
      for ( vector<double>::size_type j = 0 ; j < m_VibFreq.size() ; ++j ) {
        qtot /= (1.0 - exp(-beta*m_VibFreq[j])) ;
      }
      qtot *= sqrt(pi/(m_MmtIntA * m_MmtIntB * m_MmtIntC))*(pow(beta,-1.5))/m_Sym ;
      formatFloat(cout, temp,  6,  7) ;
      formatFloat(cout, qtot,  6, 15) ;
      formatFloat(cout, sumc,  6, 15) ;
      formatFloat(cout, sumg,  6, 15) ;
      cout << endl ;

      //Add to XML document
      PersistPtr ppItem = ppList->XmlWriteElement("me:densityOfStates");
      ppItem->XmlWriteValueElement("me:T",    temp, 6);
      ppItem->XmlWriteValueElement("me:qtot", qtot, 6) ;
      ppItem->XmlWriteValueElement("me:sumc", sumc, 6) ;
      ppItem->XmlWriteValueElement("me:sumg", sumg, 6) ;

    }

  }

  //
  // Calculate the average grain energy and then number of states per grain.
  //
  void ModelledMolecule::calcGrainAverages() {

    m_egrn.resize(GetSys()->MAXGrn()) ;
    m_gdos.resize(GetSys()->MAXGrn()) ;

    //    int igsz = MAXCELL/MAXGRN ;

    // Check that there are enough cells.

    if (GetSys()->getGrainSize() < 1) {
      stringstream errorMsg;
      errorMsg << "Not enought Cells to produce requested number of Grains.";
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      exit(1) ;
    }

    int idx1 = 0 ;
    int idx2 = 0 ;

    for (int i = 0 ; i < GetSys()->MAXGrn() ; ++i ) {

      int idx3 = idx1 ;

      // Calculate the number of states in a grain.

      double smt = 0.0 ;
      for (int j = 0 ; j < GetSys()->getGrainSize() ; ++j, ++idx1 )
          smt += m_cellDOS[idx1] ;

      // Calculate average energy of the grain if it contains sum states.

      if ( smt > 0.0 ) {

        double smat = 0.0 ;
        for (int j = 0 ; j < GetSys()->getGrainSize() ; ++j, ++idx3 )
            smat += m_cellEne[idx3] * m_cellDOS[idx3] ;

        m_gdos[idx2] = smt ;
        m_egrn[idx2] = smat/smt ;
        idx2++ ;
      }
    }

    // Issue warning if number of grains produced is less that requested.

    if ( idx2 < GetSys()->MAXGrn() ) {
      stringstream errorMsg;
      errorMsg << "Number of grains produced is less than requested" << endl
               << "Number of grains requested: " << GetSys()->MAXGrn() << endl
               << "Number of grains produced : " << idx2 << ".";
      obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
    }
  }
}//namespace
