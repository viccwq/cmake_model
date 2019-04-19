#!/bin/bash
curpath=`dirname "$(readlink -f "$0")"`
sourcepath=$curpath

echo $curpath
echo $sourcepath

if [ -d ${curpath}/install/x64 ]; then
    echo find ${curpath}/install/x64
    if [ -d ${curpath}/bin/x64 ]; then
        cp -v ${curpath}/bin/x64/*.* ${curpath}/install/x64/
    fi
    if [ -d ${curpath}/lib/x64 ]; then
        cp -v ${curpath}/lib/x64/*.* ${curpath}/install/x64/
    fi
fi

if [ -d ${curpath}/install/x86 ]; then
    echo find ${curpath}/install/x86
    if [ -d ${curpath}/bin/x86 ]; then
        cp -v ${curpath}/bin/x86/*.* ${curpath}/install/x86/
    fi
    if [ -d ${curpath}/lib/x86 ]; then
        cp -v ${curpath}/lib/x86/*.* ${curpath}/install/x86/
    fi
fi

read -p "Press any key to finish..." var
