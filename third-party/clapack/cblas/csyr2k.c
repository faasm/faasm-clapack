
/*  -- translated by f2c (version 19940927).
   You must link the resulting object file with the libraries:
	-lf2c -lm   (in that order)
*/

#include "f2c.h"
#include "cblas.h"

/* Subroutine */ int csyr2k_(char *uplo, char *trans, integer *n, integer *k, 
	complex *alpha, complex *a, integer *lda, complex *b, integer *ldb, 
	complex *beta, complex *c, integer *ldc)
{


    /* System generated locals */
    integer a_dim1, a_offset, b_dim1, b_offset, c_dim1, c_offset, i__1, i__2, 
	    i__3, i__4, i__5, i__6, i__7;
    complex q__1, q__2, q__3, q__4, q__5;

    /* Local variables */
    static integer info;
    static complex temp1, temp2;
    static integer i, j, l;
    extern logical lsame_(char *, char *);
    static integer nrowa;
    static logical upper;
    extern /* Subroutine */ int xerbla_(char *, integer *);


/*  Purpose   
    =======   

    CSYR2K  performs one of the symmetric rank 2k operations   

       C := alpha*A*B' + alpha*B*A' + beta*C,   

    or   

       C := alpha*A'*B + alpha*B'*A + beta*C,   

    where  alpha and beta  are scalars,  C is an  n by n symmetric matrix 
  
    and  A and B  are  n by k  matrices  in the  first  case  and  k by n 
  
    matrices in the second case.   

    Parameters   
    ==========   

    UPLO   - CHARACTER*1.   
             On  entry,   UPLO  specifies  whether  the  upper  or  lower 
  
             triangular  part  of the  array  C  is to be  referenced  as 
  
             follows:   

                UPLO = 'U' or 'u'   Only the  upper triangular part of  C 
  
                                    is to be referenced.   

                UPLO = 'L' or 'l'   Only the  lower triangular part of  C 
  
                                    is to be referenced.   

             Unchanged on exit.   

    TRANS  - CHARACTER*1.   
             On entry,  TRANS  specifies the operation to be performed as 
  
             follows:   

                TRANS = 'N' or 'n'    C := alpha*A*B' + alpha*B*A' +   
                                           beta*C.   

                TRANS = 'T' or 't'    C := alpha*A'*B + alpha*B'*A +   
                                           beta*C.   

             Unchanged on exit.   

    N      - INTEGER.   
             On entry,  N specifies the order of the matrix C.  N must be 
  
             at least zero.   
             Unchanged on exit.   

    K      - INTEGER.   
             On entry with  TRANS = 'N' or 'n',  K  specifies  the number 
  
             of  columns  of the  matrices  A and B,  and on  entry  with 
  
             TRANS = 'T' or 't',  K  specifies  the number of rows of the 
  
             matrices  A and B.  K must be at least zero.   
             Unchanged on exit.   

    ALPHA  - COMPLEX         .   
             On entry, ALPHA specifies the scalar alpha.   
             Unchanged on exit.   

    A      - COMPLEX          array of DIMENSION ( LDA, ka ), where ka is 
  
             k  when  TRANS = 'N' or 'n',  and is  n  otherwise.   
             Before entry with  TRANS = 'N' or 'n',  the  leading  n by k 
  
             part of the array  A  must contain the matrix  A,  otherwise 
  
             the leading  k by n  part of the array  A  must contain  the 
  
             matrix A.   
             Unchanged on exit.   

    LDA    - INTEGER.   
             On entry, LDA specifies the first dimension of A as declared 
  
             in  the  calling  (sub)  program.   When  TRANS = 'N' or 'n' 
  
             then  LDA must be at least  max( 1, n ), otherwise  LDA must 
  
             be at least  max( 1, k ).   
             Unchanged on exit.   

    B      - COMPLEX          array of DIMENSION ( LDB, kb ), where kb is 
  
             k  when  TRANS = 'N' or 'n',  and is  n  otherwise.   
             Before entry with  TRANS = 'N' or 'n',  the  leading  n by k 
  
             part of the array  B  must contain the matrix  B,  otherwise 
  
             the leading  k by n  part of the array  B  must contain  the 
  
             matrix B.   
             Unchanged on exit.   

    LDB    - INTEGER.   
             On entry, LDB specifies the first dimension of B as declared 
  
             in  the  calling  (sub)  program.   When  TRANS = 'N' or 'n' 
  
             then  LDB must be at least  max( 1, n ), otherwise  LDB must 
  
             be at least  max( 1, k ).   
             Unchanged on exit.   

    BETA   - COMPLEX         .   
             On entry, BETA specifies the scalar beta.   
             Unchanged on exit.   

    C      - COMPLEX          array of DIMENSION ( LDC, n ).   
             Before entry  with  UPLO = 'U' or 'u',  the leading  n by n 
  
             upper triangular part of the array C must contain the upper 
  
             triangular part  of the  symmetric matrix  and the strictly 
  
             lower triangular part of C is not referenced.  On exit, the 
  
             upper triangular part of the array  C is overwritten by the 
  
             upper triangular part of the updated matrix.   
             Before entry  with  UPLO = 'L' or 'l',  the leading  n by n 
  
             lower triangular part of the array C must contain the lower 
  
             triangular part  of the  symmetric matrix  and the strictly 
  
             upper triangular part of C is not referenced.  On exit, the 
  
             lower triangular part of the array  C is overwritten by the 
  
             lower triangular part of the updated matrix.   

    LDC    - INTEGER.   
             On entry, LDC specifies the first dimension of C as declared 
  
             in  the  calling  (sub)  program.   LDC  must  be  at  least 
  
             max( 1, n ).   
             Unchanged on exit.   


    Level 3 Blas routine.   

    -- Written on 8-February-1989.   
       Jack Dongarra, Argonne National Laboratory.   
       Iain Duff, AERE Harwell.   
       Jeremy Du Croz, Numerical Algorithms Group Ltd.   
       Sven Hammarling, Numerical Algorithms Group Ltd.   



       Test the input parameters.   

    
   Parameter adjustments   
       Function Body */

#define A(I,J) a[(I)-1 + ((J)-1)* ( *lda)]
#define B(I,J) b[(I)-1 + ((J)-1)* ( *ldb)]
#define C(I,J) c[(I)-1 + ((J)-1)* ( *ldc)]

    if (lsame_(trans, "N")) {
	nrowa = *n;
    } else {
	nrowa = *k;
    }
    upper = lsame_(uplo, "U");

    info = 0;
    if (! upper && ! lsame_(uplo, "L")) {
	info = 1;
    } else if (! lsame_(trans, "N") && ! lsame_(trans, "T")) {
	info = 2;
    } else if (*n < 0) {
	info = 3;
    } else if (*k < 0) {
	info = 4;
    } else if (*lda < max(1,nrowa)) {
	info = 7;
    } else if (*ldb < max(1,nrowa)) {
	info = 9;
    } else if (*ldc < max(1,*n)) {
	info = 12;
    }
    if (info != 0) {
	xerbla_("CSYR2K", &info);
	return 0;
    }

/*     Quick return if possible. */

    if (*n == 0 || (alpha->r == 0.f && alpha->i == 0.f || *k == 0) && (
	    beta->r == 1.f && beta->i == 0.f)) {
	return 0;
    }

/*     And when  alpha.eq.zero. */

    if (alpha->r == 0.f && alpha->i == 0.f) {
	if (upper) {
	    if (beta->r == 0.f && beta->i == 0.f) {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L10: */
		    }
/* L20: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L30: */
		    }
/* L40: */
		}
	    }
	} else {
	    if (beta->r == 0.f && beta->i == 0.f) {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L50: */
		    }
/* L60: */
		}
	    } else {
		i__1 = *n;
		for (j = 1; j <= *n; ++j) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L70: */
		    }
/* L80: */
		}
	    }
	}
	return 0;
    }

/*     Start the operations. */

    if (lsame_(trans, "N")) {

/*        Form  C := alpha*A*B' + alpha*B*A' + C. */

	if (upper) {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (beta->r == 0.f && beta->i == 0.f) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L90: */
		    }
		} else if (beta->r != 1.f || beta->i != 0.f) {
		    i__2 = j;
		    for (i = 1; i <= j; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L100: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    i__3 = j + l * a_dim1;
		    i__4 = j + l * b_dim1;
		    if (A(j,l).r != 0.f || A(j,l).i != 0.f || (B(j,l).r != 
			    0.f || B(j,l).i != 0.f)) {
			i__3 = j + l * b_dim1;
			q__1.r = alpha->r * B(j,l).r - alpha->i * B(j,l).i, 
				q__1.i = alpha->r * B(j,l).i + alpha->i * B(j,l).r;
			temp1.r = q__1.r, temp1.i = q__1.i;
			i__3 = j + l * a_dim1;
			q__1.r = alpha->r * A(j,l).r - alpha->i * A(j,l).i, 
				q__1.i = alpha->r * A(j,l).i + alpha->i * A(j,l).r;
			temp2.r = q__1.r, temp2.i = q__1.i;
			i__3 = j;
			for (i = 1; i <= j; ++i) {
			    i__4 = i + j * c_dim1;
			    i__5 = i + j * c_dim1;
			    i__6 = i + l * a_dim1;
			    q__3.r = A(i,l).r * temp1.r - A(i,l).i * 
				    temp1.i, q__3.i = A(i,l).r * temp1.i + A(i,l).i * temp1.r;
			    q__2.r = C(i,j).r + q__3.r, q__2.i = C(i,j).i + 
				    q__3.i;
			    i__7 = i + l * b_dim1;
			    q__4.r = B(i,l).r * temp2.r - B(i,l).i * 
				    temp2.i, q__4.i = B(i,l).r * temp2.i + B(i,l).i * temp2.r;
			    q__1.r = q__2.r + q__4.r, q__1.i = q__2.i + 
				    q__4.i;
			    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L110: */
			}
		    }
/* L120: */
		}
/* L130: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		if (beta->r == 0.f && beta->i == 0.f) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			i__3 = i + j * c_dim1;
			C(i,j).r = 0.f, C(i,j).i = 0.f;
/* L140: */
		    }
		} else if (beta->r != 1.f || beta->i != 0.f) {
		    i__2 = *n;
		    for (i = j; i <= *n; ++i) {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__1.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__1.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L150: */
		    }
		}
		i__2 = *k;
		for (l = 1; l <= *k; ++l) {
		    i__3 = j + l * a_dim1;
		    i__4 = j + l * b_dim1;
		    if (A(j,l).r != 0.f || A(j,l).i != 0.f || (B(j,l).r != 
			    0.f || B(j,l).i != 0.f)) {
			i__3 = j + l * b_dim1;
			q__1.r = alpha->r * B(j,l).r - alpha->i * B(j,l).i, 
				q__1.i = alpha->r * B(j,l).i + alpha->i * B(j,l).r;
			temp1.r = q__1.r, temp1.i = q__1.i;
			i__3 = j + l * a_dim1;
			q__1.r = alpha->r * A(j,l).r - alpha->i * A(j,l).i, 
				q__1.i = alpha->r * A(j,l).i + alpha->i * A(j,l).r;
			temp2.r = q__1.r, temp2.i = q__1.i;
			i__3 = *n;
			for (i = j; i <= *n; ++i) {
			    i__4 = i + j * c_dim1;
			    i__5 = i + j * c_dim1;
			    i__6 = i + l * a_dim1;
			    q__3.r = A(i,l).r * temp1.r - A(i,l).i * 
				    temp1.i, q__3.i = A(i,l).r * temp1.i + A(i,l).i * temp1.r;
			    q__2.r = C(i,j).r + q__3.r, q__2.i = C(i,j).i + 
				    q__3.i;
			    i__7 = i + l * b_dim1;
			    q__4.r = B(i,l).r * temp2.r - B(i,l).i * 
				    temp2.i, q__4.i = B(i,l).r * temp2.i + B(i,l).i * temp2.r;
			    q__1.r = q__2.r + q__4.r, q__1.i = q__2.i + 
				    q__4.i;
			    C(i,j).r = q__1.r, C(i,j).i = q__1.i;
/* L160: */
			}
		    }
/* L170: */
		}
/* L180: */
	    }
	}
    } else {

/*        Form  C := alpha*A'*B + alpha*B'*A + C. */

	if (upper) {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = j;
		for (i = 1; i <= j; ++i) {
		    temp1.r = 0.f, temp1.i = 0.f;
		    temp2.r = 0.f, temp2.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			i__4 = l + i * a_dim1;
			i__5 = l + j * b_dim1;
			q__2.r = A(l,i).r * B(l,j).r - A(l,i).i * B(l,j)
				.i, q__2.i = A(l,i).r * B(l,j).i + A(l,i)
				.i * B(l,j).r;
			q__1.r = temp1.r + q__2.r, q__1.i = temp1.i + q__2.i;
			temp1.r = q__1.r, temp1.i = q__1.i;
			i__4 = l + i * b_dim1;
			i__5 = l + j * a_dim1;
			q__2.r = B(l,i).r * A(l,j).r - B(l,i).i * A(l,j)
				.i, q__2.i = B(l,i).r * A(l,j).i + B(l,i)
				.i * A(l,j).r;
			q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
			temp2.r = q__1.r, temp2.i = q__1.i;
/* L190: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp1.r - alpha->i * temp1.i, 
				q__2.i = alpha->r * temp1.i + alpha->i * 
				temp1.r;
			q__3.r = alpha->r * temp2.r - alpha->i * temp2.i, 
				q__3.i = alpha->r * temp2.i + alpha->i * 
				temp2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__4.r = alpha->r * temp1.r - alpha->i * temp1.i, 
				q__4.i = alpha->r * temp1.i + alpha->i * 
				temp1.r;
			q__2.r = q__3.r + q__4.r, q__2.i = q__3.i + q__4.i;
			q__5.r = alpha->r * temp2.r - alpha->i * temp2.i, 
				q__5.i = alpha->r * temp2.i + alpha->i * 
				temp2.r;
			q__1.r = q__2.r + q__5.r, q__1.i = q__2.i + q__5.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L200: */
		}
/* L210: */
	    }
	} else {
	    i__1 = *n;
	    for (j = 1; j <= *n; ++j) {
		i__2 = *n;
		for (i = j; i <= *n; ++i) {
		    temp1.r = 0.f, temp1.i = 0.f;
		    temp2.r = 0.f, temp2.i = 0.f;
		    i__3 = *k;
		    for (l = 1; l <= *k; ++l) {
			i__4 = l + i * a_dim1;
			i__5 = l + j * b_dim1;
			q__2.r = A(l,i).r * B(l,j).r - A(l,i).i * B(l,j)
				.i, q__2.i = A(l,i).r * B(l,j).i + A(l,i)
				.i * B(l,j).r;
			q__1.r = temp1.r + q__2.r, q__1.i = temp1.i + q__2.i;
			temp1.r = q__1.r, temp1.i = q__1.i;
			i__4 = l + i * b_dim1;
			i__5 = l + j * a_dim1;
			q__2.r = B(l,i).r * A(l,j).r - B(l,i).i * A(l,j)
				.i, q__2.i = B(l,i).r * A(l,j).i + B(l,i)
				.i * A(l,j).r;
			q__1.r = temp2.r + q__2.r, q__1.i = temp2.i + q__2.i;
			temp2.r = q__1.r, temp2.i = q__1.i;
/* L220: */
		    }
		    if (beta->r == 0.f && beta->i == 0.f) {
			i__3 = i + j * c_dim1;
			q__2.r = alpha->r * temp1.r - alpha->i * temp1.i, 
				q__2.i = alpha->r * temp1.i + alpha->i * 
				temp1.r;
			q__3.r = alpha->r * temp2.r - alpha->i * temp2.i, 
				q__3.i = alpha->r * temp2.i + alpha->i * 
				temp2.r;
			q__1.r = q__2.r + q__3.r, q__1.i = q__2.i + q__3.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    } else {
			i__3 = i + j * c_dim1;
			i__4 = i + j * c_dim1;
			q__3.r = beta->r * C(i,j).r - beta->i * C(i,j).i, 
				q__3.i = beta->r * C(i,j).i + beta->i * C(i,j).r;
			q__4.r = alpha->r * temp1.r - alpha->i * temp1.i, 
				q__4.i = alpha->r * temp1.i + alpha->i * 
				temp1.r;
			q__2.r = q__3.r + q__4.r, q__2.i = q__3.i + q__4.i;
			q__5.r = alpha->r * temp2.r - alpha->i * temp2.i, 
				q__5.i = alpha->r * temp2.i + alpha->i * 
				temp2.r;
			q__1.r = q__2.r + q__5.r, q__1.i = q__2.i + q__5.i;
			C(i,j).r = q__1.r, C(i,j).i = q__1.i;
		    }
/* L230: */
		}
/* L240: */
	    }
	}
    }

    return 0;

/*     End of CSYR2K. */

} /* csyr2k_ */

