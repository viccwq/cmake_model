::@echo on
@echo off
set curpath=%~dp0
set sourcepath=%curpath%

if exist %curpath%install\x64 (
	echo "find %curpath%install\x64"
	if exist %curpath%bin\x64 (
		xcopy /y /c /r "%curpath%bin\x64\*.*" "%curpath%install\x64\")
	if exist %curpath%lib\x64 (
		xcopy /y /c /r "%curpath%lib\x64\*.*" "%curpath%install\x64\")
)

if exist %curpath%install\x86 (
	echo "find %curpath%install\x86"
	if exist %curpath%bin\x86 (
		xcopy /y /c /r "%curpath%bin\x86\*.*" "%curpath%install\x86\")
	if exist %curpath%lib\x64 (
		xcopy /y /c /r "%curpath%lib\x86\*.*" "%curpath%install\x86\")
)

pause
