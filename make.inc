CC=$(WASM_CC)
CXX=$(WASM_CXX)
CPP=$(WASM_CPP)
NM=$(WASM_NM)
LD=$(WASM_LD)

_FLAGS=$(WASM_CFLAGS_NO_QUOTES) -Xlinker --no-entry -nostdlib
LDFLAGS=$(_FLAGS) -Xlinker --stack-first -Xlinker --shared
CFLAGS=$(_FLAGS) -O3 -I$(TOPDIR)/INCLUDE -fPIC 

SHELL = /bin/sh

PLAT = _WASM

LOADER    = $(CC)
LOADOPTS  =
NOOPT     = -O0 -I$(TOPDIR)/INCLUDE
DRVCFLAGS = $(CFLAGS)
F2CCFLAGS = $(CFLAGS)

TIMER    = INT_CPU_TIME

AR=$(WASM_AR)
ARCH     = $(AR)
ARCHFLAGS= cr
RANLIB   = $(WASM_RANLIB)

CBLASLIB      = ../cblas$(PLAT).so
BLASLIB      = ../../blas$(PLAT).so

XBLASLIB     =

LAPACKLIB    = lapack$(PLAT).so
F2CLIB       = ../../F2CLIBS/libf2c.so

# Not used in our case
TMGLIB       = tmglib$(PLAT).a
EIGSRCLIB    = eigsrc$(PLAT).a
LINSRCLIB    = linsrc$(PLAT).a
