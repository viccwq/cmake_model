#ifndef __VXLPORTABLE_H__
#define __VXLPORTABLE_H__

#include <iostream>
#include <stdexcept>
#include <vector>

#include "vxlCommonMacros.h"
#include "vxlErrorCode.h"
#include "vxlPortableTypes.h"

#ifdef _WIN32
#include <windows.h>
#else if defined __linux__
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <sys/timeb.h>
#include <sys/stat.h>
#include <unistd.h>
#include <errno.h>
#include <pwd.h>
#include <stdarg.h>
#endif

#ifdef _WIN32
#else if defined __linux__
#define _vsnprintf_s     vsnprintf
#define Sleep(x)         usleep((x)*1000)
#define printf_s         printf
#define sprintf_s        sprintf
#endif

//! create a directory
/*!
    \strDir : directory to be created, which must be in UNIX style and can only accept alphabets, digits, dots or underlines
*/
VXL_EXECUTION_STATUS CreateDir(IN const std::string &strDir);

//! delete a directory
/*!
    \strDir : directory to be deleted, which must be in UNIX style and can only accept alphabets, digits, dots or underlines
*/
VXL_EXECUTION_STATUS DeleteDir(IN const std::string &strDir);

#ifdef __linux__
//! get current user path (only in linux defined)
/*!
    \userPath : get the current user path in linux
*/
void VcaGetUserPath(OUT std::string &userPath);
#endif

//! get the current path
/*!
    \path : the path of current module
*/
VXL_EXECUTION_STATUS GetCurPath(OUT std::string &path);

//! get the config file absolute path
/*!
    \strCfgPath : input relative path of the config file
    \strPath    : output absolute path of the config file
*/
VXL_EXECUTION_STATUS GetConfigFilePath(
    IN  const char* const strCfgPath,
    OUT std::string       &strPath);

//! split file absolute path into dir/name/ext
/*!
    \filePath : input path of the file
    \fileDir  : output directory of the file
    \fileName : output name of the file
    \fileExt  : output suffix of the file
*/
VXL_EXECUTION_STATUS SplitFilePath(
    IN  const std::string &filePath,
    OUT       std::string &fileDir,
    OUT       std::string &fileName,
    OUT       std::string &fileExt);

//! read all the content of the input file into a string
//  note: the point to the output string returned must be freed after used
/*!
    \filePath : input path of the input file
*/
char* ReadStringFromFile(IN const char* const filePath);

//! remove the invalid characters(space, \t, \r, \n) at the end of the string
/*!
    \s : input string
*/
void RemoveLastInvalidCharacters(IN OUT std::string &s);

//! read all the lines of the input file into a string vector (one element of the vector is one single line)
//  and remove all the invalid characters(space, \t, \r, \n) at the end of the line
/*!
    \filePath : input path of the input file
*/
std::vector<std::string> ReadFileIntoString(IN const char* const filePath);

#endif //__VXLPORTABLEFUNCS_H__
