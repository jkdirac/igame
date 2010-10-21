#!/bin/sh

# set path
export QTDIR="C:\\Qt\\2010.05\\qt"
export PATH="$PATH;C:\\Qt\\2010.05\\qt\\bin"
export PATH="$PATH;C:\\Qt\\2010.05\\bin;C:\\Qt\\2010.05\\mingw\\bin"

# run
./iGaME.exe "$*"
