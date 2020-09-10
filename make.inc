CC=$(WASM_CC)
CXX=$(WASM_CXX)
CPP=$(WASM_CPP)
NM=$(WASM_NM)
LD=$(WASM_LD)

# NOTE - if we want to use fPIC here, we have to specify
# --target=wasm32-unknown-emscripten -fPIC
# However, we want to try and compile everything as static libs

_FLAGS=$(WASM_CFLAGS_NO_QUOTES) -Xlinker --no-entry -Xlinker --no-gc-sections 
LDFLAGS=$(_FLAGS) -Xlinker --stack-first 
CFLAGS=$(_FLAGS) -O3 -I$(TOPDIR)/INCLUDE 

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

CBLASLIB      = ../cblas$(PLAT).a
BLASLIB      = ../../blas$(PLAT).a

XBLASLIB     =

LAPACKLIB    = lapack$(PLAT).a
F2CLIB       = ../../F2CLIBS/libf2c.a

# Not used in our case
TMGLIB       = tmglib$(PLAT).a
EIGSRCLIB    = eigsrc$(PLAT).a
LINSRCLIB    = linsrc$(PLAT).a
