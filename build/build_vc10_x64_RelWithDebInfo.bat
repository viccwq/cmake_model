::@echo on
@echo off
set curpath=%~dp0
set sourcepath=%curpath%

rd /s /q %curpath%build_vc10_x64_RelWithDebInfo

mkdir %curpath%build_vc10_x64_RelWithDebInfo & pushd %curpath%build_vc10_x64_RelWithDebInfo
cmake %sourcepath%.. -G "Visual Studio 10 2010 Win64" -DCMAKE_CONFIGURATION_TYPES=RelWithDebInfo
popd
cmake --build %curpath%build_vc10_x64_RelWithDebInfo --config RelWithDebInfo
