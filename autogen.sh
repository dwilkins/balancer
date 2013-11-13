#!/bin/sh
if [ -e 'Makefile.am' ] ; then
    echo "Makefile.am Exists - reconfiguring..."
    autoreconf --force --install -I config -I m4
    exit
fi
echo "Lets get your project started!"

echo '## Process this file with automake to produce Makefile.in' >> Makefile.am
echo No Makefile.am
