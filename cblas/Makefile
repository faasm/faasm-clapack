TOPDIR=..
include $(TOPDIR)/make.inc

SRCS = $(wildcard *.c)
OBJS = $(patsubst %.c,%.o,$(SRCS))

all: $(CBLASLIB)

$(CBLASLIB): $(OBJS)
	$(ARCH) $(ARCHFLAGS) $@ $(OBJS)
	$(RANLIB) $@

%.o: %.c 
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o

