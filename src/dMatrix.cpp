//-------------------------------------------------------------------------------------------
//
// dMatrix.cpp
//
// Author: Struan Robertson
// Date:   18/June/2006
//
// EISPACK functions for diagonalizing a symmetric matrix.
//
//-------------------------------------------------------------------------------------------
#include <cmath>
#include <stdio.h>
#include "dMatrix.h"

//-------------------------------------------------------------------------------------------
// EISPACK tred2 function.
//
// Householder reduction of matrix a to tridiagonal form.
//   Algorithm: Martin et al., Num. Math. 11, 181-195, 1968.
//   Ref: Smith et al., Matrix Eigensystem Routines -- EISPACK Guide
//   Springer-Verlag, 1976, pp. 489-494.
//   W H Press et al., Numerical Recipes in C, Cambridge U P,
//   1988, pp. 373-374.
//-------------------------------------------------------------------------------------------
namespace mesmer
{
    //dd_real dd; //This will compile

    void dMatrix::tred2(double **a, int n, double *d, double *e)
    {
        int l, k, j, i;
        double scale, hh, h, g, f;

        for (i=n;i>=2;--i) {
            l=i-1;
            h=scale=0.0;
            if (l > 1) {

                for (k=1;k<=l;++k)
                    scale += fabs(a[i-1][k-1]);
                if (scale == 0.0)
                    e[i-1]=a[i-1][l-1];
                else {
                    for (k=1;k<=l;++k) {
                        a[i-1][k-1] /= scale;
                        h += a[i-1][k-1]*a[i-1][k-1];
                    }
                    f=a[i-1][l-1];
                    g = f>0 ? -sqrt(h) : sqrt(h);
                    e[i-1]=scale*g;
                    h -= f*g;
                    a[i-1][l-1]=f-g;
                    f=0.0;
                    for (j=1;j<=l;++j) {
                        /* Next statement can be omitted if eigenvectors not wanted */
                        a[j-1][i-1]=a[i-1][j-1]/h;
                        g=0.0;

                        for (k=1;k<=j;++k)
                            g += a[j-1][k-1]*a[i-1][k-1];

                        for (k=j+1;k<=l;++k)
                            g += a[k-1][j-1]*a[i-1][k-1];
                        e[j-1]=g/h;
                        f += e[j-1]*a[i-1][j-1];
                    }
                    hh=f/(h+h);
                    for (j=1;j<=l;++j) {
                        f=a[i-1][j-1];
                        e[j-1]=g=e[j-1]-hh*f;

                        for (k=1;k<=j;++k)
                            a[j-1][k-1] -= (f*e[k-1]+g*a[i-1][k-1]);
                    }
                }
            } else
                e[i-1]=a[i-1][l-1];
            d[i-1]=h;
        }
        /* Next statement can be omitted if eigenvectors not wanted */
        d[0]=0.0;
        e[0]=0.0;
        /* Contents of this loop can be omitted if eigenvectors not
        wanted except for statement d[i-1]=a[i-1][i-1]; */
        for (i=1;i<=n;++i) {
            l=i-1;
            if (d[i-1] != .0) {
                for (j=1;j<=l;++j) {
                    g=0.0;

                    for (k=1;k<=l;++k)
                        g += a[i-1][k-1]*a[k-1][j-1];

                    for (k=1;k<=l;++k)
                        a[k-1][j-1] -= g*a[k-1][i-1];
                }
            }
            d[i-1]=a[i-1][i-1];
            a[i-1][i-1]=1.0;

            for (j=1;j<=l;++j) a[j-1][i-1]=a[i-1][j-1]=0.0;
        }
    }

    //-------------------------------------------------------------------------------------------
    // EISPACK tqli function.
    //
    // QL algorithm with implicit shifts, to determine the eigenvalues and eigenvectors of a real,
    // symmetric, tridiagonal matrix, or of a real, symmetric matrix previously reduced by tred2.
    //
    // On input:
    //    d[1..n] contains the diagonal elements of the tridiagonal matrix.
    //    e[1..n] contains the subdiagonal elements of the tridiagonal matrix.
    // with e[1] arbitrary.
    // On output:
    //    d[1..n] returns the eigenvalues.
    //    e[1..n] is destroyed.
    //
    // When finding only the eigenvalues, several lines may be omitted, as noted in the comments.
    //
    // If the eigenvectors of a tridiagonal matrix are desired, the matrix z[1..n][1..n] is input
    // as the identity matrix. If the eigenvectors of a matrix that has been reduced by tred2 are
    // required, then z is input as the matrix output by tred2. In either case, the kth column of
    // z returns the normalized eigenvector corresponding to d[k].
    //
    //-------------------------------------------------------------------------------------------
    void dMatrix::tqli(double *d, double *e, int n, double **z)
    {
        int m,l,iter,i,k;
        double s,r,p,g,f,dd,c,b;

        for (i=2;i<=n;++i) e[i-2]=e[i-1];
        e[n-1]=0.0;
        for (l=1;l<=n;++l) {
            iter=0;
            do {
                for (m=l;m<=n-1;++m) {
                    dd=fabs(d[m-1])+fabs(d[m]);
                    if (fabs(e[m-1])+dd == dd) break;
                }
                if (m != l) {
                    // if (iter++ == 30) fprintf(stderr, "Too many iterations in TQLI");
                    if (iter++ == 60) fprintf(stderr, "Too many iterations in TQLI");
                    /* CHL
                    Source: http://www.nr.com/forum/showthread.php?t=592
                    I hope that bellow words will be useful for you.
                    See thread under the title: Possible convergence problems in svdcmp, jacobi, tqli, hqr by Saul Teukolsky
                    in Forum: Official Bug Reports with known bugs. May be this is a reason of slow convergency.
                    It is good check, that matrix is symmetric and to work with double accuracy. I have known also versions
                    with increased number of iterations (200 for example). But I think that this experimental number is right
                    in any case: if you have not convergency for 30 iterations, there is no convergency at all.
                    SVD method used in book is an intrinsic iterative procedure, 30 iterations is a good number to
                    convergency up to numerical accuracy. Evgeny
                    */
                    g=(d[l]-d[l-1])/(2.0*e[l-1]);
                    r=sqrt((g*g)+1.0);
                    g=d[m-1]-d[l-1]+e[l-1]/(g + (g<0 ? -fabs(r) : fabs(r)));
                    s=c=1.0;
                    p=0.0;
                    for (i=m-1;i>=l;--i) {
                        f=s*e[i-1];
                        b=c*e[i-1];
                        if (fabs(f) >= fabs(g)) {
                            c=g/f;
                            r=sqrt((c*c)+1.0);
                            e[i]=f*r;
                            c *= (s=1.0/r);
                        } else {
                            s=f/g;
                            r=sqrt((s*s)+1.0);
                            e[i]=g*r;
                            s *= (c=1.0/r);
                        }
                        g=d[i]-p;
                        r=(d[i-1]-g)*s+2.0*c*b;
                        p=s*r;
                        d[i]=g+p;
                        g=c*r-b;
                        /* Next loop can be omitted if eigenvectors not wanted */

                        for (k=1;k<=n;++k) {
                            f=z[k-1][i];
                            z[k-1][i]=s*z[k-1][i-1]+c*f;
                            z[k-1][i-1]=c*z[k-1][i-1]-s*f;
                        }
                    }
                    d[l-1]=d[l-1]-p;
                    e[l-1]=g;
                    e[m-1]=0.0;
                }
            } while (m != l);
        }

        // Order eigenvalues and eigenvectors.

        for (int ii = 1; ii < n; ++ii) {
            i = ii - 1;
            k = i;
            p = d[i];
            for (int j = ii; j < n; ++j) {
                if (d[j] < p) {
                    k = j;
                    p = d[j];
                }
            }
            if (k!=i) {
                d[k] = d[i];
                d[i] = p;
                for (int j = 0; j < n; ++j) {
                    p = z[j][i];
                    z[j][i] = z[j][k];
                    z[j][k] = p;
                }
            }
        }

    }

    //-------------------------------------------------------------------------------------------
    // EISPACK pythag function.
    //
    // Finds sqrtl(a**2+b**2) without overflow or destructive underflow.
    //
    //-------------------------------------------------------------------------------------------
    double dMatrix::pythag(double a, double b)
    {
        double p,r,s,t,u;
        if (fabs(a) > fabs(b)) p = fabs(a);
        else p = fabs(b);
        if (p == 0.) goto label_1;
        if (fabs(a) > fabs(b)) r = fabs(b);
        else r = fabs(a);
        r = (r/p)*(r/p);

label_2: t = 4. + r;
        if (t == 4.) goto label_1;
        s = r/t;
        u = 1. + 2. *s;
        p *= u;
        r = ((s/u)*(s/u))*r;

        goto label_2;
label_1: return(p);
    }

    //
    // NR LU methods for linear equation solving.
    //
    void dMatrix::ludcmp(double **a,  int n, int *indx, double d) {

        const double TINY = 1.0e-20 ;
        int i, imax, j, k ;
        double big, dum, sum, temp ;

        double *work = new double[n] ;
        d = 1.0 ;
        for (i = 1; i < n ; i++) {
            big = 0.0 ;
            for (j = 0; j < n ; j++) {
                if ((temp = fabs(a[i][j])) > big)
                    big = temp ;
            }
            if (big == 0.0) {
                fprintf(stderr, "Singular Matrix in routine ludcmp");
                exit(0) ;
            }
            work[i] = 1.0/big ;
        }

        for (j = 0; j < n ; j++) {
            for (i = 0; i < j ; i++) {
                sum = a[i][j] ;
                for (k = 0; k < i ; k++) 
                    sum -= a[i][k]*a[k][j] ;

                a[i][j] = sum ;
            }
            big = 0.0 ;
            for (i = j; i < n; i++) {
                sum = a[i][j] ;
                for (k = 0; k < j ; k++) 
                    sum -= a[i][k]*a[k][j] ;

                a[i][j] = sum ;

                if ( (dum = work[i]*fabs(sum)) >= big) {
                    big = dum ;
                    imax = i ;
                }
            }
            if (j != imax) {
                for (k = 0; k < n; k++) {
                    dum = a[imax][k] ;
                    a[imax][k] = a[j][k] ;
                    a[j][k] = dum ;
                }
                d = -d ;
                work[imax] = work[j] ;
            }
            indx[j] = imax ;
            if (a[i][j] == 0.0)
                a[j][i] = TINY ;

            if (j != n-1) {
                dum = 1.0/(a[j][i]) ;
                for (i = j+1; i < n; i++)
                    a[i][j] = dum ;
            }

        }

        delete [] work ;

    }

    void dMatrix::lubksb(double **a,  int n, int *indx, double* b) {

        int i, ii = 0, ip, j ;
        double sum ;

        for (i = 0; i < n; i++) {
            ip = indx[i] ;
            sum = b[ip] ;
            b[ip] = b[i] ;
            if (ii != 0) {
                for (j = ii-1; j < i; j++) 
                    sum -= a[i][j]*b[j] ;
            } else {
                if (sum != 0.0) 
                    ii = i+1 ;
                b[i] = sum ;
            }
        }
        for (i = n-1; i >= 0; i--) {
            sum = b[i] ;
            for (j=i+1; j < n; j++) 
                sum -= a[i][j]*b[j] ;
            b[i] = sum/a[i][j] ;
        }
    }

}//namespacer mesmer
