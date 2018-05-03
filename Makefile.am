#
#
#

SUBDIRS = src

MAINTAINERCLEANFILES = \
        Makefile.in config.h.in configure \
        install-sh ltmain.sh missing mkinstalldirs \
        compile depcomp config.log config.status \
        config.guess config.sub acinclude.m4 aclocal.m4 \
        build-stamp

DEPCLEANFILES = config.log configure

EXTRA_DIST = \
        autogen.sh \
	debian/changelog \
	debian/compat \
	debian/control \
	debian/copyright \
	debian/conbtdialogs-dev.install \
	debian/rules \
	conbtdialogs.pc.in
        
pkgconfigdir = $(libdir)/pkgconfig
nodist_pkgconfig_DATA = conbtdialogs.pc
