#!/bin/bash
curpath=`dirname "$(readlink -f "$0")"`
sourcepath=$curpath

echo $curpath
echo $sourcepath

rm -rf $curpath/build_MSYS_RelWD
mkdir $curpath/build_MSYS_RelWD
cd $curpath/build_MSYS_RelWD

cmake $sourcepath/.. -DCMAKE_BUILD_TYPE=RelWithDebInfo -G "MSYS Makefiles"
make

cd ../;sh ./install_lib.sh
