::@echo on
@echo off
set curpath=%~dp0
set sourcepath=%curpath%

rd /s /q %curpath%build_vc10_x64_Debug

mkdir %curpath%build_vc10_x64_Debug & pushd %curpath%build_vc10_x64_Debug
cmake %sourcepath%.. -G "Visual Studio 10 2010 Win64" -DCMAKE_CONFIGURATION_TYPES=Debug
popd
cmake --build %curpath%build_vc10_x64_Debug --config Debug
