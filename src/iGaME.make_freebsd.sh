#!/bin/sh

# set path
export QTDIR="/home/soimort/qtsdk-2010.05/qt"
export PATH="$PATH;/home/soimort/qtsdk-2010.05/qt/bin"
export PATH="$PATH;/home/soimort/qtsdk-2010.05/bin"
export QMAKESPEC="freebsd-g++"

# qmake
/home/soimort/qtsdk-2010.05/qt/bin/qmake iGaME.pro

# make
make
