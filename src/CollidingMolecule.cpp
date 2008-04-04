//
// CollidingMolecule.cpp
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
  CollidingMolecule::CollidingMolecule(const MesmerEnv& Env) : ModelledMolecule(Env),
    m_DeltaEdown(0.0),
    m_collisionFrequency(0.0),
    m_ncolloptrsize(0),
    m_DeltaEdown_chk(-1),
    m_egme(NULL)
  {}

  CollidingMolecule::~CollidingMolecule()
  {
    if (m_DeltaEdown_chk == 0){
      stringstream errorMsg;
      errorMsg << "m_DeltaEdown is provided but not used in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
    }
    if (m_egme != NULL) delete m_egme ;
  }

  //
  //Initialization
  //
  bool CollidingMolecule::InitializeMolecule(PersistPtr pp)
  {
    stringstream errorMsg;
    PersistPtr oldpp = pp;

    //Read base class parameters first
    if(!ModelledMolecule::InitializeMolecule(pp)){
      stringstream errorMsg;
      errorMsg << "InitializeMolecule failed for " << getName()
      << " before constructing CollidingMolecule.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      setFlag(true);
    }

    pp = oldpp;

    PersistPtr ppPropList = pp->XmlMoveTo("propertyList");
    if(!ppPropList)
        ppPropList=pp; //Be forgiving; we can get by without a propertyList element

    const char* txt;

    txt= ppPropList->XmlReadProperty("me:sigma");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:sigma in " << getName()
               << ". Default value " << sigmaDefault << " is used.\n";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      // sigma and epsilon are not always necessary.
    }
    else { istringstream idata(txt); double sigma(0.); idata >> sigma; setSigma(sigma);}

    txt= ppPropList->XmlReadProperty("me:epsilon");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:epsilon in " << getName()
               << ". Default value " << epsilonDefault << " is used.\n";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      // sigma and epsilon are not always necessary.
    }
    else { istringstream idata(txt); double epsilon(0.); idata >> epsilon; setEpsilon(epsilon);} //extra block ensures idata is initiallised

    txt= ppPropList->XmlReadProperty("me:deltaEDown");
    if(!txt){
      stringstream errorMsg;
      errorMsg << "Cannot find argument me:deltaEDown in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obWarning);
      //setFlag(true);
      // deltaEDown is not always necessary. Hoever, it is not wise to provide a default value.
    }
    else { istringstream idata(txt); idata >> m_DeltaEdown; m_DeltaEdown_chk = 0;}

    if (getFlag()){
      stringstream errorMsg;
      errorMsg << "Error(s) while initializing: " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      return false;
    }
    return true;
  }

  double CollidingMolecule::get_collisionFrequency() const {
    return m_collisionFrequency ;
  } ;

  void CollidingMolecule::set_colloptrsize(int ncolloptrsize) {
    m_ncolloptrsize = ncolloptrsize ;
  } ;

  int  CollidingMolecule::get_colloptrsize() const {
    return m_ncolloptrsize ;
  } ;


  void   CollidingMolecule::setDeltaEdown(double value)        {
    m_DeltaEdown = value;
    m_DeltaEdown_chk = 0;
  } ;

  double CollidingMolecule::getDeltaEdown()                    {
    if (m_DeltaEdown_chk >= 0){
      ++m_DeltaEdown_chk;
      return m_DeltaEdown ;
    }
    else{
      stringstream errorMsg;
      errorMsg << "m_DeltaEdown was not defined but requested in " << getName();
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      exit(1);
    }
  } ;

  //
  // Initialize the Collision Operator.
  //
  bool CollidingMolecule::initCollisionOperator(double beta, Molecule *pBathGasMolecule)
  {
    // If density of states have not already been calcualted then do so.

    if (!m_cellDOS.size())
      calcDensityOfStates() ;

    // Calculate the collision frequency.
    m_collisionFrequency = collisionFrequency(beta, getEnv().conc, pBathGasMolecule) ;

    // Calculate the collision operator.
    if (!collisionOperator(beta)){
      cerr << "Failed building collision operator";
      return false;
    }
    return true;
  }

  //
  // Calculate collision operator
  //
  bool CollidingMolecule::collisionOperator(double beta)
  {
    if (test_rotConsts() < 0) return true;
    //
    //     i) Determine Probabilities of Energy Transfer.
    //    ii) Normalisation of Probability matrix.
    //   iii) Symmetrise Collision Matrix.
    //

    int i, j;
    int MaximumGrain = getEnv().MaxGrn;

    if(!m_DeltaEdown){
      stringstream errorMsg;
      errorMsg << "me:deltaEDown is necessary for " << getName() << ". Correct input file to remove this error.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
      return false;
    }

    double alpha = 1.0/m_DeltaEdown ;

    // Allocate memory.
    if (m_egme) delete m_egme ;                       // Delete any existing matrix.
    m_egme = new dMatrix(MaximumGrain) ;              // Collision operator matrix.

    // Initialisation and error checking.
    for ( i = 0 ; i < MaximumGrain ; ++i ) {
      if (m_grainDOS[i] <= 0.0) {
        cerr << "Data indicates that grain " << i << " of the current colliding molecule has no states.";
        return false;
      }
    }

    if (debugFlag) ctest << "alpha = " << alpha << ", m_DeltaEdown = " << m_DeltaEdown << ", beta = " << beta << endl;

    // The collision operator.
    for ( i = 0 ; i < MaximumGrain ; ++i ) {
      double ei = m_grainEne[i] ;
      double ni = m_grainDOS[i] ;
      for ( j = i ; j < MaximumGrain ; ++j ) {

        // Transfer to lower Energy -
        (*m_egme)[i][j] = exp(-alpha*(m_grainEne[j] - ei)) ;

        // Transfer to higher Energy (via detailed balance) -
        (*m_egme)[j][i] = (*m_egme)[i][j] * (m_grainDOS[j]/ni)*exp(-beta*(m_grainEne[j] - ei)) ;
      }
    }

    //check collision operator
    if (collisionOperatorCheck){
      ctest << "\nCollision operator check before normalisation:\n";
      (*m_egme).showFinalBits(7);
    }

    //Normalisation
    m_egme->normalize();

    if (collisionOperatorCheck){
      ctest << "\nCollision operator check after normalisation:\n";
      (*m_egme).showFinalBits(7);
    }

    // Symmetrization of the collision matrix.
    if (1){
      vector<double> work(MaximumGrain,0.0) ; // Work space.
      for ( i = 0 ; i < MaximumGrain ; ++i ) {
        double ei = log(m_grainDOS[i]) - beta*m_grainEne[i] + 10.0 ;
        ei = exp(ei) ;
        work[i] = sqrt(ei) ;
      }
      for ( i = 1 ; i < MaximumGrain ; ++i ) {
        for ( j = 0 ; j < i ; ++j ) {
          (*m_egme)[j][i] *= (work[i]/work[j]) ;
          (*m_egme)[i][j]  = (*m_egme)[j][i] ;
        }
      }
    }

    if (collisionOperatorCheck){
      ctest << "\nCollision operator check after symmetrisation:\n";
      (*m_egme).showFinalBits(7);
    }

    //account for collisional loss by subrtacting unity from the leading diagonal.
    for ( i = 0 ; i < MaximumGrain ; ++i ) (*m_egme)[i][i] -= 1.0 ;

    if (getEnv().collisionOCSEnabled){
      ctest << endl << "Collision operator column Sums" << endl << "{" << endl ;
      for ( i = 0 ; i < MaximumGrain ; ++i ) {
        double columnSum(0.0) ;
        for ( j = 0 ; j < MaximumGrain ; ++j ){
          columnSum += to_double((*m_egme)[j][i]) ;
        }
        ctest << columnSum << endl ;
      }
      ctest << "}" << endl;
    }


    return true;
  }

  //
  // Calculate collision frequency.
  //
  double CollidingMolecule::collisionFrequency(double beta, const double conc, Molecule *pBathGasMolecule)
  {
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

    double temp = 1.0/(boltzmann_RCpK*beta) ;

    // Calculate collision parameter averages.
    double bthMass = 0.0;
    bthMass = pBathGasMolecule->getMass();

    double bthSigma = 0.0;
    bthSigma = pBathGasMolecule->getSigma();

    if (!bthSigma)
      cerr << "me:sigma is necessary for " << pBathGasMolecule->getName()
           << ". Correct input file to remove this error." << endl;

    double bthEpsilon = 0.0;
    bthEpsilon = pBathGasMolecule->getEpsilon();

    if (!bthEpsilon)
      cerr << "me:epsilon is necessary for " << pBathGasMolecule->getName()
           << ". Correct input file to remove this error.";
    double mr   = getMass();
    double mu   = amu * getMass() * bthMass/(getMass() + bthMass) ;
    double eam  = sqrt(getEpsilon() * bthEpsilon) ;
    double sam  = (getSigma() + bthSigma) * 0.5;
    double tstr = temp / eam;

    if (debugFlag)
      ctest << "mu = " << mu << ", mr = " << mr << ", bthMass = " << bthMass << ", eam = " << eam << ", sam = " << sam
            << ", tstr = " << tstr << ", beta = " << beta << ", temp = " << temp << ", conc = " << conc << endl;

    // Calculate collision integral.
    double collFrq = A * exp(-log(tstr) * B) + C * exp(-D * tstr) + E * exp(-F * tstr) ;
    if (debugFlag) ctest << "collFrq = " << collFrq << endl;

    // Calculate molecular collision frequency.
    collFrq *= (M_PI * sam * sam * 1.0e-20 * sqrt(8. * boltzmann_C * temp/(M_PI * mu))) ;
    if (debugFlag) ctest << "collFrq = " << collFrq << endl;
    // Calculate overall collision frequency.
    collFrq *= (conc * 1.0e6) ;

    if (debugFlag) ctest << "Collision frequency of " << getName() << " is " << collFrq << endl;

    return collFrq;
  }

  //
  // Calculate a reaction matrix element.
  //
  double CollidingMolecule::matrixElement(int eigveci, int eigvecj, vector<double> &k, int ndim)
  {
    double sum = 0.0 ;
    for (int i = 0 ; i < ndim ; ++i){
      sum +=  k[i]* to_double((*m_egme)[i][eigveci]*(*m_egme)[i][eigvecj]) ;
    }
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

    int smsize = static_cast<int>(CollOptr->size()) ;
    //int MaximumGrain = getEnv().MaxGrn;

    if (debugFlag) ctest << "smsize = " << smsize << ", locate = " << locate << ", size = " << size << endl;
    // Check there is enough space in system matrix.

    if (locate + size > smsize) {
      stringstream errorMsg;
      errorMsg << "Error in the size of the system matrix.";
      meErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obError);
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

    if (collisionOperatorCheck){
      ctest << "\nSystem collision operator check after copied from egme:\n";
      (*CollOptr).showFinalBits(8);
    }

  }

}//namespace