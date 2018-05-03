#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_INIT(libconbtui, 1.4.3, aapo.makela@nokia.com)
AM_INIT_AUTOMAKE(AC_PACKAGE_NAME, AC_PACKAGE_VERSION)
AC_COPYRIGHT([Copyright (C) Nokia Corporation 2006])
AM_CONFIG_HEADER(config.h)

# Checks for programs.
AC_PROG_CC
AC_PROG_CPP
AC_PROG_INSTALL
AC_PROG_LN_S
AC_PROG_MAKE_SET
AC_PROG_LIBTOOL

# Checks for libraries

# Checks for header files.

# Checks for typedefs, structures, and compiler characteristics.

# Checks for library functions.

# Doxygen documentation
AC_ARG_ENABLE(docs,     [  --enable-docs        build DOXYGEN documentation (requires Doxygen)],enable_docs=$enableval,enable_docs=auto)

AC_PATH_PROG(DOXYGEN, doxygen, no)

AC_MSG_CHECKING([whether to build Doxygen documentation])

if test x$DOXYGEN = xno ; then
    have_doxygen=no
else
    have_doxygen=yes
fi
if test x$enable_docs = xauto ; then
    if test x$have_doxygen = xno ; then
        enable_docs=no
    else
        enable_docs=yes
    fi
fi

if test x$enable_docs = xyes; then
    if test x$have_doxygen = xno; then
        AC_MSG_ERROR([Building Doxygen docs explicitly required, but Doxygen not found])
    else
        AC_MSG_RESULT(yes)
    fi
else
    AC_MSG_RESULT(no)
fi

AM_CONDITIONAL(DOXYGEN_DOCS_ENABLED, test x$enable_docs = xyes)


AC_OUTPUT([ \
	  Makefile \
	  conbtdialogs.pc \
	  src/Makefile \
	  ])
