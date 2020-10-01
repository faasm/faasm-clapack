CC=$(WASM_CC)
CXX=$(WASM_CXX)
CPP=$(WASM_CPP)
NM=$(WASM_NM)
LD=$(WASM_CC)

# Link flags for static libs
#_FLAGS=$(WASM_CFLAGS_NO_QUOTES) 
#LDFLAGS=$(_FLAGS) -Xlinker --stack-first 
#CFLAGS=$(_FLAGS) -O3 -I$(TOPDIR)/INCLUDE 

# Flags for shared libs
_FLAGS=$(WASM_CFLAGS_NO_QUOTES) \
    -D__wasi__ \
    -nostdlib -nostdlib++ \
    -fPIC \
    --target=wasm32-unknown-emscripten \
    -Xlinker --no-entry \
    -Xlinker --shared \
    -Xlinker --export-all \
    -Xlinker --no-gc-sections \
    -I$(TOPDIR)/INCLUDE 
LDFLAGS=$(_FLAGS)
CFLAGS=$(_FLAGS)

SHELL = /bin/sh

PLAT = _WASM

LOADER    = $(CC)
LOADOPTS  =
NOOPT     = -O0 -I$(TOPDIR)/INCLUDE
DRVCFLAGS = $(CFLAGS)
F2CCFLAGS = $(CFLAGS)

TIMER    = INT_CPU_TIME

AR       = $(WASM_AR)
ARCH     = $(AR)
ARCHFLAGS= cr
RANLIB   = $(WASM_RANLIB)

# Change for static/ dynamic libs
LIBEXT=.so

CBLASLIB     = ../cblas$(PLAT)$(LIBEXT)
BLASLIB      = ../../blas$(PLAT)$(LIBEXT)

XBLASLIB     =

LAPACKLIB    = lapack$(PLAT)$(LIBEXT)
F2CLIB       = ../../F2CLIBS/libf2c$(LIBEXT)

# Not used in Faasm
TMGLIB       = junk_tmglib$(LIBEXT)
EIGSRCLIB    = junk_eigsrc$(LIBEXT)
LINSRCLIB    = junk_linsrc$(LIBEXT)
