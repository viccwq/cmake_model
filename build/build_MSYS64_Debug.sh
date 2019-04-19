#!/bin/bash
curpath=`dirname "$(readlink -f "$0")"`
sourcepath=$curpath

echo $curpath
echo $sourcepath

rm -rf $curpath/build_MSYS_Debug
mkdir $curpath/build_MSYS_Debug
cd $curpath/build_MSYS_Debug

cmake $sourcepath/.. -DCMAKE_BUILD_TYPE=Debug -G "MSYS Makefiles"
make

cd ../;sh ./install_lib.sh
