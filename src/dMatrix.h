#ifndef GUARD_dMatrix_h
#define GUARD_dMatrix_h

//-------------------------------------------------------------------------------------------
//
// dMatrix.h
//
// Author: Struan Robertson
// Date:   30/Mar/2003
//
// This header file contains the declaration of the dMatrix class.  This class inherits from
// Matrix and wraps calls to LAPACK functions.
//
//-------------------------------------------------------------------------------------------
#include "MesmerPrecision.h"
#include "Matrix.h"
#include <string>

#if defined USE_CXSC
#define fabs abs
#endif

class dMatrix : public Matrix<MesmerHP> {

public:

  // Constructor
  dMatrix(int n) : Matrix<MesmerHP>(n) { } ;

  // Wrapped call to LAPACK routine to diagonalise matrix.
  void diagonalize(double *rr) {

    int size ;
    size = static_cast<int>(m_msize) ;

    //  Allocate memory for work array
    MesmerHP *work = new MesmerHP[size] ;
    MesmerHP *rrProxy = new MesmerHP[size] ;
    
    tred2(m_matrix, size, rrProxy, work) ;
    tqli(rrProxy, work, size, m_matrix) ;

    for (int i = 0; i < size; ++i){
#if defined (USE_QD) || defined(USE_DD)  //GUARD_USE_QD_USE_DD
      rr[i] = to_double(rrProxy[i]);
#elif defined (USE_CXSC)
      rr[i] = _double(_real(rrProxy[i]));
#else
      rr[i] = rrProxy[i];
#endif  //GUARD_USE_QD_USE_DD
    }
    delete [] work ;
  }

private:

  //
  // EISPACK methods for diagonalizing matrix.
  //
  void    tred2   (MesmerHP **a, int n, MesmerHP *d, MesmerHP *e) ;
  void    tqli    (MesmerHP *d, MesmerHP *e, int n, MesmerHP **z) ;
  MesmerHP  pythag  (MesmerHP a, MesmerHP b) ;

} ;


#endif // GUARD_dMatrix_h
