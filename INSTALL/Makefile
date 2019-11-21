TOPDIR=..
include $(TOPDIR)/make.inc
F2CLIB       = $(TOPDIR)/F2CLIBS/libf2c.a
THIS_LIBS=-lm -ldlmalloc

.SUFFIXES : .o .c 
all:  testlsame testslamch testdlamch testsecond testdsecnd testieee testversion 

testlsame:  lsame.o lsametst.o
	$(CC) $(LOADOPTS)   -o testlsame lsame.o lsametst.o $(F2CLIB) $(THIS_LIBS)

testslamch: slamch.o lsame.o slamchtst.o
	$(CC) $(LOADOPTS)   -o testslamch slamch.o lsame.o slamchtst.o $(F2CLIB) $(THIS_LIBS)

testdlamch: dlamch.o lsame.o dlamchtst.o
	$(CC) $(LOADOPTS)   -o testdlamch dlamch.o lsame.o dlamchtst.o $(F2CLIB) $(THIS_LIBS)

testsecond: second.o secondtst.o
	$(CC) $(LOADOPTS)   -o testsecond second.o secondtst.o $(F2CLIB) $(THIS_LIBS)

testdsecnd: dsecnd.o dsecndtst.o
	$(CC) $(LOADOPTS)   -o testdsecnd dsecnd.o dsecndtst.o $(F2CLIB) $(THIS_LIBS)

testieee: tstiee.o
	$(CC) $(LOADOPTS)   -o testieee tstiee.o $(F2CLIB) $(THIS_LIBS)

testversion: ilaver.o LAPACK_version.o
	    $(CC) $(LOADOPTS)   -o testversion ilaver.o LAPACK_version.o $(F2CLIB) $(THIS_LIBS)

clean:
	rm -f *.o

slamch.o: slamch.c ; $(CC) $(NOOPT) -c $< -o $@
dlamch.o: dlamch.c ; $(CC) $(NOOPT) -c $< -o $@

.c.o: ; $(CC) $(CFLAGS) -c $< -o $@
