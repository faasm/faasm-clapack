
/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblas.h"

/* Subroutine */ int ctbmv_(char *uplo, char *trans, char *diag, integer *n, 
	integer *k, complex *a, integer *lda, complex *x, integer *incx)
{


    /* System generated locals */
    integer a_dim1, a_offset, i__1, i__2, i__3, i__4, i__5;
    complex q__1, q__2, q__3;

    /* Builtin functions */
    void r_cnjg(complex *, complex *);

    /* Local variables */
    static integer info;
    static complex temp;
    static integer i, j, l;
    extern logical lsame_(char *, char *);
    static integer kplus1, ix, jx, kx;
    extern /* Subroutine */ int xerbla_(char *, integer *);
    static logical noconj, nounit;


/*  Purpose   
    =======   

    CTBMV  performs one of the matrix-vector operations   

       x := A*x,   or   x := A'*x,   or   x := conjg( A' )*x,   

    where x is an n element vector and  A is an n by n unit, or non-unit, 
  
    upper or lower triangular band matrix, with ( k + 1 ) diagonals.   

    Parameters   
    ==========   

    UPLO   - CHARACTER*1.   
             On entry, UPLO specifies whether the matrix is an upper or   
             lower triangular matrix as follows:   

                UPLO = 'U' or 'u'   A is an upper triangular matrix.   

                UPLO = 'L' or 'l'   A is a lower triangular matrix.   

             Unchanged on exit.   

    TRANS  - CHARACTER*1.   
             On entry, TRANS specifies the operation to be performed as   
             follows:   

                TRANS = 'N' or 'n'   x := A*x.   

                TRANS = 'T' or 't'   x := A'*x.   

                TRANS = 'C' or 'c'   x := conjg( A' )*x.   

             Unchanged on exit.   

    DIAG   - CHARACTER*1.   
             On entry, DIAG specifies whether or not A is unit   
             triangular as follows:   

                DIAG = 'U' or 'u'   A is assumed to be unit triangular.   

                DIAG = 'N' or 'n'   A is not assumed to be unit   
                                    triangular.   

             Unchanged on exit.   

    N      - INTEGER.   
             On entry, N specifies the order of the matrix A.   
             N must be at least zero.   
             Unchanged on exit.   

    K      - INTEGER.   
             On entry with UPLO = 'U' or 'u', K specifies the number of   
             super-diagonals of the matrix A.   
             On entry with UPLO = 'L' or 'l', K specifies the number of   
             sub-diagonals of the matrix A.   
             K must satisfy  0 .le. K.   
             Unchanged on exit.   

    A      - COMPLEX          array of DIMENSION ( LDA, n ).   
             Before entry with UPLO = 'U' or 'u', the leading ( k + 1 )   
             by n part of the array A must contain the upper triangular   
             band part of the matrix of coefficients, supplied column by 
  
             column, with the leading diagonal of the matrix in row   
             ( k + 1 ) of the array, the first super-diagonal starting at 
  
             position 2 in row k, and so on. The top left k by k triangle 
  
             of the array A is not referenced.   
             The following program segment will transfer an upper   
             triangular band matrix from conventional full matrix storage 
  
             to band storage:   

                   DO 20, J = 1, N   
                      M = K + 1 - J   
                      DO 10, I = MAX( 1, J - K ), J   
                         A( M + I, J ) = matrix( I, J )   
                10    CONTINUE   
                20 CONTINUE   

             Before entry with UPLO = 'L' or 'l', the leading ( k + 1 )   
             by n part of the array A must contain the lower triangular   
             band part of the matrix of coefficients, supplied column by 
  
             column, with the leading diagonal of the matrix in row 1 of 
  
             the array, the first sub-diagonal starting at position 1 in 
  
             row 2, and so on. The bottom right k by k triangle of the   
             array A is not referenced.   
             The following program segment will transfer a lower   
             triangular band matrix from conventional full matrix storage 
  
             to band storage:   

                   DO 20, J = 1, N   
                      M = 1 - J   
                      DO 10, I = J, MIN( N, J + K )   
                         A( M + I, J ) = matrix( I, J )   
                10    CONTINUE   
                20 CONTINUE   

             Note that when DIAG = 'U' or 'u' the elements of the array A 
  
             corresponding to the diagonal elements of the matrix are not 
  
             referenced, but are assumed to be unity.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in the calling (sub) program. LDA must be at least   
             ( k + 1 ).   
             Unchanged on exit.   

    X      - COMPLEX          array of dimension at least   
             ( 1 + ( n - 1 )*abs( INCX ) ).   
             Before entry, the incremented array X must contain the n   
             element vector x. On exit, X is overwritten with the   
             tranformed vector x.   

    INCX   - INTEGER.   
             On entry, INCX specifies the increment for the elements of   
             X. INCX must not be zero.   
             Unchanged on exit.   


    Level 2 Blas routine.   

    -- Written on 22-October-1986.   
       Jack Dongarra, Argonne National Lab.   
       Jeremy Du Croz, Nag Central Office.   
       Sven Hammarling, Nag Central Office.   
       Richard Hanson, Sandia National Labs.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */
#define X(I) x[(I)-1]

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]

    info = 0;
    if (! lsame_(uplo, "U") && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, "T") &&
	     ! lsame_(trans, "C")) {
	info = 2;
    } else if (! lsame_(diag, "U") && ! lsame_(diag, "N")) {
	info = 3;
    } else if (*n < 0) {
	info = 4;
    } else if (*k < 0) {
	info = 5;
    } else if (*lda < *k + 1) {
	info = 7;
    } else if (*incx == 0) {
	info = 9;
    }
    if (info != 0) {
	xerbla_("CTBMV ", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0) {
	return 0;
    }

    noconj = lsame_(trans, "T");
    nounit = lsame_(diag, "N");

/*     Set up the start point in X if the increment is not unity. This   
       will be  ( N - 1 )*INCX   too small for descending loops. */

    if (*incx <= 0) {
	kx = 1 - (*n - 1) * *incx;
    } else if (*incx != 1) {
	kx = 1;
    }

/*     Start the operations. In this version the elements of A are   
       accessed sequentially with one pass through A. */

    if (lsame_(trans, "N")) {

/*         Form  x := A*x. */

	if (lsame_(uplo, "U")) {
	    kplus1 = *k + 1;
	    if (*incx == 1) {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = j;
		    if (X(j).r != 0.f || X(j).i != 0.f) {
			i__2 = j;
			temp.r = X(j).r, temp.i = X(j).i;
			l = kplus1 - j;
/* Computing MAX */
			i__2 = 1, i__3 = j - *k;
			i__4 = j - 1;
			for (i = max(1,j-*k); i <= j-1; ++i) {
			    i__2 = i;
			    i__3 = i;
			    i__5 = l + i + j * a_dim1;
			    q__2.r = temp.r * A(l+i,j).r - temp.i * A(l+i,j).i, 
				    q__2.i = temp.r * A(l+i,j).i + temp.i * A(l+i,j).r;
			    q__1.r = X(i).r + q__2.r, q__1.i = X(i).i + 
				    q__2.i;
			    X(i).r = q__1.r, X(i).i = q__1.i;
/* L10: */
			}
			if (nounit) {
			    i__4 = j;
			    i__2 = j;
			    i__3 = kplus1 + j * a_dim1;
			    q__1.r = X(j).r * A(kplus1,j).r - X(j).i * A(kplus1,j).i, q__1.i = X(j).r * A(kplus1,j).i + 
				    X(j).i * A(kplus1,j).r;
			    X(j).r = q__1.r, X(j).i = q__1.i;
			}
		    }
/* L20: */
		}
	    } else {
		jx = kx;
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__4 = jx;
		    if (X(jx).r != 0.f || X(jx).i != 0.f) {
			i__4 = jx;
			temp.r = X(jx).r, temp.i = X(jx).i;
			ix = kx;
			l = kplus1 - j;
/* Computing MAX */
			i__4 = 1, i__2 = j - *k;
			i__3 = j - 1;
			for (i = max(1,j-*k); i <= j-1; ++i) {
			    i__4 = ix;
			    i__2 = ix;
			    i__5 = l + i + j * a_dim1;
			    q__2.r = temp.r * A(l+i,j).r - temp.i * A(l+i,j).i, 
				    q__2.i = temp.r * A(l+i,j).i + temp.i * A(l+i,j).r;
			    q__1.r = X(ix).r + q__2.r, q__1.i = X(ix).i + 
				    q__2.i;
			    X(ix).r = q__1.r, X(ix).i = q__1.i;
			    ix += *incx;
/* L30: */
			}
			if (nounit) {
			    i__3 = jx;
			    i__4 = jx;
			    i__2 = kplus1 + j * a_dim1;
			    q__1.r = X(jx).r * A(kplus1,j).r - X(jx).i * A(kplus1,j).i, q__1.i = X(jx).r * A(kplus1,j).i + 
				    X(jx).i * A(kplus1,j).r;
			    X(jx).r = q__1.r, X(jx).i = q__1.i;
			}
		    }
		    jx += *incx;
		    if (j > *k) {
			kx += *incx;
		    }
/* L40: */
		}
	    }
	} else {
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    i__1 = j;
		    if (X(j).r != 0.f || X(j).i != 0.f) {
			i__1 = j;
			temp.r = X(j).r, temp.i = X(j).i;
			l = 1 - j;
/* Computing MIN */
			i__1 = *n, i__3 = j + *k;
			i__4 = j + 1;
			for (i = min(*n,j+*k); i >= j+1; --i) {
			    i__1 = i;
			    i__3 = i;
			    i__2 = l + i + j * a_dim1;
			    q__2.r = temp.r * A(l+i,j).r - temp.i * A(l+i,j).i, 
				    q__2.i = temp.r * A(l+i,j).i + temp.i * A(l+i,j).r;
			    q__1.r = X(i).r + q__2.r, q__1.i = X(i).i + 
				    q__2.i;
			    X(i).r = q__1.r, X(i).i = q__1.i;
/* L50: */
			}
			if (nounit) {
			    i__4 = j;
			    i__1 = j;
			    i__3 = j * a_dim1 + 1;
			    q__1.r = X(j).r * A(1,j).r - X(j).i * A(1,j).i, q__1.i = X(j).r * A(1,j).i + 
				    X(j).i * A(1,j).r;
			    X(j).r = q__1.r, X(j).i = q__1.i;
			}
		    }
/* L60: */
		}
	    } else {
		kx += (*n - 1) * *incx;
		jx = kx;
		for (j = *n; j >= 1; --j) {
		    i__4 = jx;
		    if (X(jx).r != 0.f || X(jx).i != 0.f) {
			i__4 = jx;
			temp.r = X(jx).r, temp.i = X(jx).i;
			ix = kx;
			l = 1 - j;
/* Computing MIN */
			i__4 = *n, i__1 = j + *k;
			i__3 = j + 1;
			for (i = min(*n,j+*k); i >= j+1; --i) {
			    i__4 = ix;
			    i__1 = ix;
			    i__2 = l + i + j * a_dim1;
			    q__2.r = temp.r * A(l+i,j).r - temp.i * A(l+i,j).i, 
				    q__2.i = temp.r * A(l+i,j).i + temp.i * A(l+i,j).r;
			    q__1.r = X(ix).r + q__2.r, q__1.i = X(ix).i + 
				    q__2.i;
			    X(ix).r = q__1.r, X(ix).i = q__1.i;
			    ix -= *incx;
/* L70: */
			}
			if (nounit) {
			    i__3 = jx;
			    i__4 = jx;
			    i__1 = j * a_dim1 + 1;
			    q__1.r = X(jx).r * A(1,j).r - X(jx).i * A(1,j).i, q__1.i = X(jx).r * A(1,j).i + 
				    X(jx).i * A(1,j).r;
			    X(jx).r = q__1.r, X(jx).i = q__1.i;
			}
		    }
		    jx -= *incx;
		    if (*n - j >= *k) {
			kx -= *incx;
		    }
/* L80: */
		}
	    }
	}
    } else {

/*        Form  x := A'*x  or  x := conjg( A' )*x. */

	if (lsame_(uplo, "U")) {
	    kplus1 = *k + 1;
	    if (*incx == 1) {
		for (j = *n; j >= 1; --j) {
		    i__3 = j;
		    temp.r = X(j).r, temp.i = X(j).i;
		    l = kplus1 - j;
		    if (noconj) {
			if (nounit) {
			    i__3 = kplus1 + j * a_dim1;
			    q__1.r = temp.r * A(kplus1,j).r - temp.i * A(kplus1,j).i, 
				    q__1.i = temp.r * A(kplus1,j).i + temp.i * A(kplus1,j).r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MAX */
			i__4 = 1, i__1 = j - *k;
			i__3 = max(i__4,i__1);
			for (i = j - 1; i >= max(1,j-*k); --i) {
			    i__4 = l + i + j * a_dim1;
			    i__1 = i;
			    q__2.r = A(l+i,j).r * X(i).r - A(l+i,j).i * X(
				    i).i, q__2.i = A(l+i,j).r * X(i).i + 
				    A(l+i,j).i * X(i).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
/* L90: */
			}
		    } else {
			if (nounit) {
			    r_cnjg(&q__2, &A(kplus1,j));
			    q__1.r = temp.r * q__2.r - temp.i * q__2.i, 
				    q__1.i = temp.r * q__2.i + temp.i * 
				    q__2.r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MAX */
			i__4 = 1, i__1 = j - *k;
			i__3 = max(i__4,i__1);
			for (i = j - 1; i >= max(1,j-*k); --i) {
			    r_cnjg(&q__3, &A(l+i,j));
			    i__4 = i;
			    q__2.r = q__3.r * X(i).r - q__3.i * X(i).i, 
				    q__2.i = q__3.r * X(i).i + q__3.i * X(
				    i).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
/* L100: */
			}
		    }
		    i__3 = j;
		    X(j).r = temp.r, X(j).i = temp.i;
/* L110: */
		}
	    } else {
		kx += (*n - 1) * *incx;
		jx = kx;
		for (j = *n; j >= 1; --j) {
		    i__3 = jx;
		    temp.r = X(jx).r, temp.i = X(jx).i;
		    kx -= *incx;
		    ix = kx;
		    l = kplus1 - j;
		    if (noconj) {
			if (nounit) {
			    i__3 = kplus1 + j * a_dim1;
			    q__1.r = temp.r * A(kplus1,j).r - temp.i * A(kplus1,j).i, 
				    q__1.i = temp.r * A(kplus1,j).i + temp.i * A(kplus1,j).r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MAX */
			i__4 = 1, i__1 = j - *k;
			i__3 = max(i__4,i__1);
			for (i = j - 1; i >= max(1,j-*k); --i) {
			    i__4 = l + i + j * a_dim1;
			    i__1 = ix;
			    q__2.r = A(l+i,j).r * X(ix).r - A(l+i,j).i * X(
				    ix).i, q__2.i = A(l+i,j).r * X(ix).i + 
				    A(l+i,j).i * X(ix).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
			    ix -= *incx;
/* L120: */
			}
		    } else {
			if (nounit) {
			    r_cnjg(&q__2, &A(kplus1,j));
			    q__1.r = temp.r * q__2.r - temp.i * q__2.i, 
				    q__1.i = temp.r * q__2.i + temp.i * 
				    q__2.r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MAX */
			i__4 = 1, i__1 = j - *k;
			i__3 = max(i__4,i__1);
			for (i = j - 1; i >= max(1,j-*k); --i) {
			    r_cnjg(&q__3, &A(l+i,j));
			    i__4 = ix;
			    q__2.r = q__3.r * X(ix).r - q__3.i * X(ix).i, 
				    q__2.i = q__3.r * X(ix).i + q__3.i * X(
				    ix).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
			    ix -= *incx;
/* L130: */
			}
		    }
		    i__3 = jx;
		    X(jx).r = temp.r, X(jx).i = temp.i;
		    jx -= *incx;
/* L140: */
		}
	    }
	} else {
	    if (*incx == 1) {
		i__3 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__4 = j;
		    temp.r = X(j).r, temp.i = X(j).i;
		    l = 1 - j;
		    if (noconj) {
			if (nounit) {
			    i__4 = j * a_dim1 + 1;
			    q__1.r = temp.r * A(1,j).r - temp.i * A(1,j).i, 
				    q__1.i = temp.r * A(1,j).i + temp.i * A(1,j).r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MIN */
			i__1 = *n, i__2 = j + *k;
			i__4 = min(i__1,i__2);
			for (i = j + 1; i <= min(*n,j+*k); ++i) {
			    i__1 = l + i + j * a_dim1;
			    i__2 = i;
			    q__2.r = A(l+i,j).r * X(i).r - A(l+i,j).i * X(
				    i).i, q__2.i = A(l+i,j).r * X(i).i + 
				    A(l+i,j).i * X(i).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
/* L150: */
			}
		    } else {
			if (nounit) {
			    r_cnjg(&q__2, &A(1,j));
			    q__1.r = temp.r * q__2.r - temp.i * q__2.i, 
				    q__1.i = temp.r * q__2.i + temp.i * 
				    q__2.r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MIN */
			i__1 = *n, i__2 = j + *k;
			i__4 = min(i__1,i__2);
			for (i = j + 1; i <= min(*n,j+*k); ++i) {
			    r_cnjg(&q__3, &A(l+i,j));
			    i__1 = i;
			    q__2.r = q__3.r * X(i).r - q__3.i * X(i).i, 
				    q__2.i = q__3.r * X(i).i + q__3.i * X(
				    i).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
/* L160: */
			}
		    }
		    i__4 = j;
		    X(j).r = temp.r, X(j).i = temp.i;
/* L170: */
		}
	    } else {
		jx = kx;
		i__3 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__4 = jx;
		    temp.r = X(jx).r, temp.i = X(jx).i;
		    kx += *incx;
		    ix = kx;
		    l = 1 - j;
		    if (noconj) {
			if (nounit) {
			    i__4 = j * a_dim1 + 1;
			    q__1.r = temp.r * A(1,j).r - temp.i * A(1,j).i, 
				    q__1.i = temp.r * A(1,j).i + temp.i * A(1,j).r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MIN */
			i__1 = *n, i__2 = j + *k;
			i__4 = min(i__1,i__2);
			for (i = j + 1; i <= min(*n,j+*k); ++i) {
			    i__1 = l + i + j * a_dim1;
			    i__2 = ix;
			    q__2.r = A(l+i,j).r * X(ix).r - A(l+i,j).i * X(
				    ix).i, q__2.i = A(l+i,j).r * X(ix).i + 
				    A(l+i,j).i * X(ix).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
			    ix += *incx;
/* L180: */
			}
		    } else {
			if (nounit) {
			    r_cnjg(&q__2, &A(1,j));
			    q__1.r = temp.r * q__2.r - temp.i * q__2.i, 
				    q__1.i = temp.r * q__2.i + temp.i * 
				    q__2.r;
			    temp.r = q__1.r, temp.i = q__1.i;
			}
/* Computing MIN */
			i__1 = *n, i__2 = j + *k;
			i__4 = min(i__1,i__2);
			for (i = j + 1; i <= min(*n,j+*k); ++i) {
			    r_cnjg(&q__3, &A(l+i,j));
			    i__1 = ix;
			    q__2.r = q__3.r * X(ix).r - q__3.i * X(ix).i, 
				    q__2.i = q__3.r * X(ix).i + q__3.i * X(
				    ix).r;
			    q__1.r = temp.r + q__2.r, q__1.i = temp.i + 
				    q__2.i;
			    temp.r = q__1.r, temp.i = q__1.i;
			    ix += *incx;
/* L190: */
			}
		    }
		    i__4 = jx;
		    X(jx).r = temp.r, X(jx).i = temp.i;
		    jx += *incx;
/* L200: */
		}
	    }
	}
    }

    return 0;

/*     End of CTBMV . */

} /* ctbmv_ */

