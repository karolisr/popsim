CC = gcc
OPTS = -Ofast -DMATHLIB_STANDALONE -DR_NO_REMAP_RMATH

# Modified version of https://gist.github.com/sighingnow/deee806603ec9274fd47
# Detect operating system in Makefile.
# Author: He Tao
# Date: 2015-05-30
DIRLIB :=
ifeq ($(OS),Windows_NT)
	DIRLIB += ../resources/windows
else
	UNAME_S := $(shell uname -s)
	ifeq ($(UNAME_S),Linux)
		DIRLIB += ../resources/linux
	endif
	ifeq ($(UNAME_S),Darwin)
		DIRLIB += ../resources/mac
	endif
endif
# ---------------------------------------------------------------------------

all: libRmath.dylib

libRmath.dylib: obj
	$(CC) $(OPTS) -shared -o \
	libRmath.dylib bd0.o bessel_i.o bessel_j.o bessel_k.o bessel_y.o beta.o \
	chebyshev.o choose.o cospi.o d1mach.o dbeta.o dbinom.o dcauchy.o dchisq.o \
	dexp.o df.o dgamma.o dgeom.o dhyper.o dlnorm.o dlogis.o dnbeta.o dnbinom.o \
	dnchisq.o dnf.o dnorm.o dnt.o dpois.o dt.o dunif.o dweibull.o fmax2.o \
	fmin2.o fprec.o fround.o fsign.o ftrunc.o gamma_cody.o gamma.o gammalims.o \
	i1mach.o imax2.o imin2.o lbeta.o lgamma.o lgammacor.o log1p.o mlutils.o \
	pbeta.o pbinom.o pcauchy.o pchisq.o pexp.o pf.o pgamma.o pgeom.o phyper.o \
	plnorm.o plogis.o pnbeta.o pnbinom.o pnchisq.o pnf.o pnorm.o pnt.o \
	polygamma.o ppois.o pt.o ptukey.o punif.o pweibull.o qbeta.o qbinom.o \
	qcauchy.o qchisq.o qexp.o qf.o qgamma.o qgeom.o qhyper.o qlnorm.o qlogis.o \
	qnbeta.o qnbinom.o qnchisq.o qnf.o qnorm.o qnt.o qpois.o qt.o qtukey.o \
	qunif.o qweibull.o rbeta.o rbinom.o rcauchy.o rchisq.o rexp.o rf.o rgamma.o \
	rgeom.o rhyper.o rlnorm.o rlogis.o rmultinom.o rnbinom.o rnchisq.o rnorm.o \
	rpois.o rt.o runif.o rweibull.o sexp.o sign.o signrank.o snorm.o stirlerr.o \
	sunif.o toms708.o wilcox.o

obj: bd0.c bessel_i.c bessel_j.c bessel_k.c bessel_y.c beta.c chebyshev.c \
     choose.c cospi.c d1mach.c dbeta.c dbinom.c dcauchy.c dchisq.c dexp.c \
     df.c dgamma.c dgeom.c dhyper.c dlnorm.c dlogis.c dnbeta.c dnbinom.c \
     dnchisq.c dnf.c dnorm.c dnt.c dpois.c dt.c dunif.c dweibull.c fmax2.c \
     fmin2.c fprec.c fround.c fsign.c ftrunc.c gamma_cody.c gamma.c \
     gammalims.c i1mach.c imax2.c imin2.c lbeta.c lgamma.c lgammacor.c \
     log1p.c mlutils.c pbeta.c pbinom.c pcauchy.c pchisq.c pexp.c pf.c \
     pgamma.c pgeom.c phyper.c plnorm.c plogis.c pnbeta.c pnbinom.c \
     pnchisq.c pnf.c pnorm.c pnt.c polygamma.c ppois.c pt.c ptukey.c punif.c \
     pweibull.c qbeta.c qbinom.c qcauchy.c qchisq.c qexp.c qf.c qgamma.c \
     qgeom.c qhyper.c qlnorm.c qlogis.c qnbeta.c qnbinom.c qnchisq.c qnf.c \
     qnorm.c qnt.c qpois.c qt.c qtukey.c qunif.c qweibull.c rbeta.c rbinom.c \
     rcauchy.c rchisq.c rexp.c rf.c rgamma.c rgeom.c rhyper.c rlnorm.c \
     rlogis.c rmultinom.c rnbinom.c rnchisq.c rnorm.c rpois.c rt.c runif.c \
     rweibull.c sexp.c sign.c signrank.c snorm.c stirlerr.c sunif.c toms708.c \
     wilcox.c
	$(CC) $(OPTS) -fPIC -c \
	bd0.c bessel_i.c bessel_j.c bessel_k.c bessel_y.c beta.c chebyshev.c \
	choose.c cospi.c d1mach.c dbeta.c dbinom.c dcauchy.c dchisq.c dexp.c df.c \
	dgamma.c dgeom.c dhyper.c dlnorm.c dlogis.c dnbeta.c dnbinom.c dnchisq.c \
	dnf.c dnorm.c dnt.c dpois.c dt.c dunif.c dweibull.c fmax2.c fmin2.c \
	fprec.c fround.c fsign.c ftrunc.c gamma_cody.c gamma.c gammalims.c i1mach.c \
	imax2.c imin2.c lbeta.c lgamma.c lgammacor.c log1p.c mlutils.c pbeta.c \
	pbinom.c pcauchy.c pchisq.c pexp.c pf.c pgamma.c pgeom.c phyper.c plnorm.c \
	plogis.c pnbeta.c pnbinom.c pnchisq.c pnf.c pnorm.c pnt.c polygamma.c \
	ppois.c pt.c ptukey.c punif.c pweibull.c qbeta.c qbinom.c qcauchy.c qchisq.c \
	qexp.c qf.c qgamma.c qgeom.c qhyper.c qlnorm.c qlogis.c qnbeta.c qnbinom.c \
	qnchisq.c qnf.c qnorm.c qnt.c qpois.c qt.c qtukey.c qunif.c qweibull.c \
	rbeta.c rbinom.c rcauchy.c rchisq.c rexp.c rf.c rgamma.c rgeom.c rhyper.c \
	rlnorm.c rlogis.c rmultinom.c rnbinom.c rnchisq.c rnorm.c rpois.c rt.c \
	runif.c rweibull.c sexp.c sign.c signrank.c snorm.c stirlerr.c sunif.c \
	toms708.c wilcox.c

clean:
	rm -f *.o

scrub: clean
	rm -f *.dylib

install: all clean
	mkdir -p $(DIRLIB)
	mv *.dylib $(DIRLIB)
