# CLAPACK and BLAS Support for Faasm

Sources:

- [CLAPACK](http://www.netlib.org/clapack/)
- [LAPACK](https://github.com/Reference-LAPACK/lapack)

Certain Makefiles rely on [Faasm](https://github.com/lsds/faasm) being checked
out at `/usr/local/code/faasm`. 

Builds are usually done with the Faasm CLI (see the [BLAS
docs](https://github.com/lsds/faasm/tree/master/docs/blas.md)).

Note that CBLAS sources aren't part of the default CLAPACK so they have been
downloaded from https://www.netlib.org/clapack/cblas.tgz and included in this
repo.
