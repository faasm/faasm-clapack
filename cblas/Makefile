TOPDIR=..
include $(TOPDIR)/make.inc

# --------------------------------------------------------
# These sources are downloaded from
# https://www.netlib.org/clapack/cblas.tgz
#
# This is not included with clapack by default as they assume
# cblas will be provided by your native blas implementation.
# --------------------------------------------------------

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(BLASLIB)

$(BLASLIB): $(OBJS)
	$(ARCH) $(ARCHFLAGS) $@ $(OBJS)
	$(RANLIB) $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

