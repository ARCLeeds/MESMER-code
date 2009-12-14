//-------------------------------------------------------------------------------------------
//
// fitting.cpp
//
// Author: Struan Robertson
// Date:   29/Nov/2009
//
// This class implements the methods to determine the minimum in the chi-squared surface.
//
//-------------------------------------------------------------------------------------------

#include "../calcmethod.h"
#include <fstream>

namespace mesmer
{
  class Fitting : public CalcMethod
  {
  public:

    Fitting(const std::string& id) : CalcMethod(id), m_nVar(0), m_A(), m_B(), m_C(), m_chi2a(0.0), m_chi2b(0.0), m_chi2c(0.0) {}

    virtual ~Fitting() {}

    //Function to do the work
    virtual bool DoCalculation(System* pSys);

  protected:

  private:

    // Perform a golden search for a specified variable.
    void LineSearch(System* pSys, const vector<double> &direction, double &currentChi2) ;

    // Bracket minimum along a given line direction.    
    void BracketMinimum(System* pSys, const vector<double> &direction) ;

    // Get the current location.
    void GetLocation(vector<double> &loc) ;

    // Set the current location.
    void SetLocation(vector<double> &loc) const ;

    // Calculate the weighted sum of two vectors.
    vector<double> VectorAdd(const double a, const vector<double> &A, const double b, const vector<double> &B) const ;

    // Calculate the cartesian length of a vector.
    double VectorLength(const vector<double> &A) const ;

    // Write out current variable values.
    void WriteVarVals() const ;

    // Check for line search convergence.
    bool CheckLineSerachConvergence(const vector<double> &X) const ;


    // Constants used in bracketing and Golden section search in a line minimizaton.
    // Note that the number tol should be an estimate of the square root of machine precision.
    static const double m_Gold ;
    static const double m_GRatio ;
    static const double m_tol ;

    // Dimension of fit.
    size_t m_nVar ;

    // Vectors to hold the position of various points during bracketing and Golden section search.
    vector<double> m_A, m_B, m_C ;

    // Values of the chi2 surface corresponding to the locations above.
    double m_chi2a, m_chi2b, m_chi2c ;

  };

  ////////////////////////////////////////////////
  //Global instance
  Fitting theFitting("fitting");
  ///////////////////////////////////////////////

  //
  // Standard constants used in line searches.
  //
  const double Fitting::m_Gold   = (3.0 - sqrt(5.0))/2.0 ;
  const double Fitting::m_GRatio = (1.0 - m_Gold)/m_Gold ;
  const double Fitting::m_tol    = 1.0e-8 ;

  bool Fitting::DoCalculation(System* pSys)
  {
    m_nVar = Rdouble::withRange().size() ;

    if (m_nVar < 1) { 

      // Return error.

      return false ;

    } else {

      //
      // Initialize position vectors.
      //
      m_A.resize(m_nVar,0.0) ;
      m_B.resize(m_nVar,0.0) ;
      m_C.resize(m_nVar,0.0) ;

      //
      // Begin by finding the starting point chi-squared value.
      //
      double chiSquare(0.0) ;

      pSys->calculate(chiSquare) ;

      //
      // Next, loop sequentially over each variable, optimizing it in each direction.
      // SHR, 29/Nov/2009: tests with the isopropyl system show that this is not optimal
      // and the something like to Powell conjugate direction method would improve the 
      // rate of convergence.
      //
      int MaxNumSteps(4) ;
      bool converged(false) ;
      double tol(0.1) ;

      WriteVarVals() ;

      for (int step(1); step <= MaxNumSteps && !converged ; step++ ){

        cout << "Step " << step << " of fitting. chiSquare = " << chiSquare << endl;

        // Determine direction of search.

        vector<double> direction(m_nVar,0.0) ;
        int varID = step % m_nVar ;
        direction[varID] = 1.0 ;

        double oldChiSquare = chiSquare ;
        LineSearch(pSys, direction, chiSquare);

        WriteVarVals() ;

        // converged = ( (oldChiSquare - chiSquare)/oldChiSquare ) < tol ;

      }

    }
    return true;
  }

  void Fitting::LineSearch(System* pSys, const vector<double> &direction, double &currentChi2) {

    static const int limit = 10 ;

    cout << endl << "Begin line search" << endl ;

    m_chi2a = currentChi2 ;

    // First bracket minimum.

    BracketMinimum(pSys, direction) ;

    // At this point the minimum should be bracketed, so 
    // use golden section search to refine the minimum.

    // x = c - m_Gold*(c - a) ;
    vector<double> X = VectorAdd( (1.0 - m_Gold), m_C, m_Gold, m_A) ;
    SetLocation(X) ;
    double chi2x ;
    pSys->calculate(chi2x);

    formatFloat(cout, m_chi2a, 6, 15) ;
    formatFloat(cout, m_chi2b, 6, 15) ;
    formatFloat(cout, chi2x, 6, 15) ;
    formatFloat(cout, m_chi2c, 6, 15) ;
    cout << endl ;

    int count = 0 ;
    while(count < limit && CheckLineSerachConvergence(X)) {
      count++ ;

      if (chi2x < m_chi2b) {
        m_A     = m_B ;
        m_chi2a = m_chi2b ;
        m_B     = X ;
        m_chi2b = chi2x ;

        // x = c - m_Gold*(c - a) ;
        X = VectorAdd( (1.0 - m_Gold), m_C, m_Gold, m_A) ;
        SetLocation(X) ;

        pSys->calculate(chi2x);

      } else {
        m_C     = X ;
        m_chi2c = chi2x ;
        X       = m_B ;
        chi2x = m_chi2b ;

        // b = a + m_Gold*(c - a) ;
        m_B = VectorAdd( (1.0 - m_Gold), m_A, m_Gold, m_C) ;
        SetLocation(m_B) ;

        pSys->calculate(m_chi2b);

      }

      formatFloat(cout, m_chi2a, 6, 15) ;
      formatFloat(cout, m_chi2b, 6, 15) ;
      formatFloat(cout, chi2x, 6, 15) ;
      formatFloat(cout, m_chi2c, 6, 15) ;
      cout << endl ;

    }

    // Save the value with the best Chi^2 value.

    if (chi2x < m_chi2b) {
      currentChi2 = chi2x ;
      SetLocation(X) ;
    } else {
      currentChi2 = m_chi2b ;
      SetLocation(m_B) ;
    }

  }

  //
  // Write out current variable values.
  //
  void Fitting::WriteVarVals() const {

    cout << endl ;
    size_t iVar ;
    for(iVar = 0 ; iVar < m_nVar ; iVar++) {

      double var = *Rdouble::withRange()[iVar] ;
      formatFloat(cout, var, 6, 15) ;

    }
    cout << endl ;

  }

  //
  // Get the current location.
  //
  void Fitting::GetLocation(vector<double> &loc) {

    if (loc.size() != m_nVar) {
      // Throw an error.
    }

    size_t iVar ;
    for(iVar = 0 ; iVar < m_nVar ; iVar++) {
      loc[iVar] = *Rdouble::withRange()[iVar] ;
    }

  }

  //
  // Set the current location.
  //
  void Fitting::SetLocation(vector<double> &loc) const {

    if (loc.size() != m_nVar) {
      // Throw an error.
    }

    size_t iVar ;
    for(iVar = 0 ; iVar < m_nVar ; iVar++) {
      *Rdouble::withRange()[iVar] = loc[iVar] ;
    }

  }

  //
  // Calculate the weighted sum of two vectors.
  //
  vector<double> Fitting::VectorAdd(const double a, const vector<double> &A, const double b, const vector<double> &B) const {

    if (A.size() != B.size()) {
      // Throw an error.
    }

    vector<double> sum(A.size(),0.0) ;
    vector<double>::size_type iVar ;
    for(iVar = 0 ; iVar < A.size() ; iVar++) {
      sum[iVar] += a*A[iVar] + b*B[iVar] ;
    }

    return sum ;

  }

  //
  // Calculate the cartesian length of a vector.
  //
  double Fitting::VectorLength(const vector<double> &A) const {

    if (A.size() == 0) {
      // Throw an error.
    }

    vector<double>::size_type iVar ;
    double sum(0.0) ;
    for(iVar = 0 ; iVar < A.size() ; iVar++) {
      sum += A[iVar]*A[iVar] ;
    }

    return sqrt(sum) ;

  }

  //
  // First catch your hare ... need to bracket the minimum. To do this
  // use the parameter limits supplied. 
  //
  void Fitting::BracketMinimum(System* pSys, const vector<double> &direction) {

    // Get the current best estimate of the location of the chi2 minimum.

    GetLocation(m_A) ;

    //
    // double diff = (a - b)/100.0 ;
    // b = a - diff ;
    // SHR 13/Dec/2009: Need some criteria, probably based on range, that can be
    // used to determine how far in the direction of search to proceed.
    //

    m_B = VectorAdd(1.0, m_A, 1.0, direction) ;

    // Calculate chi2 for new point.

    SetLocation(m_B) ;
    pSys->calculate(m_chi2b);

    // Alter the direction of search so that we are always going down hill.

    if (m_chi2a < m_chi2b) {
      vector<double> vtmp = m_A ;
      m_A = m_B ;
      m_B = vtmp ;
      double tmp = m_chi2a ;
      m_chi2a = m_chi2b ;
      m_chi2b = tmp ;
    }

    // Follow gradient down hill to estimate location of the next point.

    // c = b + m_GRatio*(b - a) ;
    m_C = VectorAdd( (1.0 + m_GRatio), m_B, (-m_GRatio), m_A) ;

    // Calculate a new value of chi2 for the new parameter value. 

    SetLocation(m_C) ;
    pSys->calculate(m_chi2c);

    formatFloat(cout, m_chi2a, 6, 15) ;
    formatFloat(cout, m_chi2b, 6, 15) ;
    formatFloat(cout, m_chi2c, 6, 15) ;
    cout << endl ;

    // Repeat the search until a minimum has been bracketed or
    // the search limit has been reached. 

    while (m_chi2c < m_chi2b) {

      // Shift values so as to maintain bracketing.
      m_A     = m_B ;
      m_chi2a = m_chi2b ;
      m_B     = m_C ;
      m_chi2b = m_chi2c ;

      // Determine next estimate of lower bracket point.

      // c = b + m_GRatio*(b - a) ;
      m_C = VectorAdd( (1.0 + m_GRatio), m_B, (-m_GRatio), m_A) ;

      SetLocation(m_C) ;
      pSys->calculate(m_chi2c);

      formatFloat(cout, m_chi2a, 6, 15) ;
      formatFloat(cout, m_chi2b, 6, 15) ;
      formatFloat(cout, m_chi2c, 6, 15) ;
      cout << endl ;

    }

  }

  //
  // Check for line search convergence.
  // fabs(|c-a|) > m_tol*(fabs(b)+fabs(x)) )
  //
  bool Fitting::CheckLineSerachConvergence(const vector<double> &X) const {

    bool converged(false) ;

    vector<double> vtmp = VectorAdd(1.0, m_C, -1.0, m_A) ;
    double interval = VectorLength(vtmp) ;

    vtmp = VectorAdd( 1.0, m_B, 1.0, X) ;
    double radius = VectorLength(vtmp) ;
    
    converged = (interval < m_tol*radius) ;

    return !converged ;
  }

}//namespace

