#!/bin/sh

set -x

# removed '-f' from intltoolized so that the '--no-fuzzy-matching' change is
# not overwritten each time

libtoolize --force --copy \
&& aclocal-1.7 \
&& autoheader \
&& automake-1.7 --foreign --add-missing --force-missing -i --copy \
&& autoconf
