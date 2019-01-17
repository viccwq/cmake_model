#include <regex>
#include <fstream>
#include "vxlPortable.h"

using namespace std;

// define the regex string macros used in file operation functions
// note:
/*
    1. all of the path or dir to input or output is in UNIX style:
       dir  - windows: x:/xx/xx       | linux : [.]/xx/xx/xx
       path - windows: x:/xx/xx/xx.xx | linux : [.]/xx/xx/xx[.xx]     (the suffix name of files in linux can be missing)
*/
#define STR_REGEX_FILE   "[0-9a-zA-Z_.]+"
#ifdef _WIN32
#define STR_REGEX_DIR    "[a-zA-Z]:(/([0-9a-zA-Z_.]+))*"
#define STR_REGEX_EXT    ".([0-9a-zA-Z]+)"
#else if defined __linux__
#define STR_REGEX_DIR    ".?(/([0-9a-zA-Z_.]+))*"
#define STR_REGEX_EXT    "(.([0-9a-zA-Z]+))?"
#endif
#define STR_REGEX_PATH   STR_REGEX_DIR "/" STR_REGEX_FILE STR_REGEX_EXT

//! create a directory
/*!
    \strDir : directory to be created, which must be in UNIX style and can only accept alphabets, digits, dots or underlines
*/
VCA_EXECUTION_STATUS CreateDir(IN const string &strDir)
{
    VCA_EXECUTION_STATUS status = VCA_FAILED;

#ifdef _WIN32
    char *pChar = NULL;
    char strDirTemp[MAX_PATH] = { 0 };
    bool flg = regex_match(strDir.c_str(), regex(STR_REGEX_DIR));
    if (!flg || strDir.size() >= MAX_PATH)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    memcpy(strDirTemp, strDir.c_str(), strDir.size());

    pChar = strchr(strDirTemp, '/');
    if (pChar == NULL)
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }

    do
    {
        pChar = strchr(++pChar, '/');
        if (pChar == NULL)
        {
            CreateDirectoryA(strDirTemp, NULL);
        }
        else
        {
            *pChar = '\0';
            CreateDirectoryA(strDirTemp, NULL);
            memcpy(strDirTemp, strDir.c_str(), strDir.size());
        }
    } while (pChar != NULL);
#else if defined __linux__
    string strDirTmp;
    std::string strDirTmp2("");
    int iPre = 0, iPos = 0, iRes = 0;
    mode_t mode = S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH;// 0755;

    bool flg = regex_match(strDir.c_str(), regex(STR_REGEX_DIR));
    if (!flg || strDir.size() >= MAX_PATH)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    strDirTmp = strDir + "/";
    while ((iPos = strDirTmp.find_first_of('/', iPre)) != std::string::npos)
    {
        strDirTmp2 = strDirTmp.substr(0, iPos++);
        iPre = iPos;

        if (strDirTmp2.size() == 0)
        {
            continue; // if leading / first time is 0 length
        }

        if ((iRes = ::mkdir(strDirTmp2.c_str(), mode)) && errno != EEXIST)
        {
            status = VCA_INVALID_INPUT_ARGS;
            goto finish;
        }
    }
#endif

    status = VCA_SUCCESSED;

finish:
    return status;
}

//! delete a directory
/*!
    \strDir : directory to be deleted, which must be in UNIX style and can only accept alphabets, digits, dots or underlines
*/
VCA_EXECUTION_STATUS DeleteDir(IN const string &strDir)
{
    VCA_EXECUTION_STATUS status = VCA_FAILED;

#ifdef _WIN32
    char strPathTemp[MAX_PATH+1] = { 0 };
    SHFILEOPSTRUCTA fileOp = { 0 };

    bool flg = regex_match(strDir.c_str(), regex(STR_REGEX_DIR));
    if (!flg || strDir.size() >= MAX_PATH)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    memcpy(strPathTemp, strDir.c_str(), strDir.size());

    strPathTemp[strDir.size()] = '\0';
    strPathTemp[strDir.size() + 1] = '\0';

    fileOp.fFlags = FOF_ALLOWUNDO | FOF_NOCONFIRMATION;
    fileOp.pFrom = strPathTemp;
    fileOp.pTo = NULL;
    fileOp.wFunc = FO_DELETE;
    // note: this function can only deal with path like: "x:/xxx/xxx\0\0"
    // 1. cannot add '/' at the end of path;
    // 2. must be end with two '\0';
    // 3. the '/' can be replaced by '\\'
    if (0 != SHFileOperationA(&fileOp))
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }
#else if defined __linux__
    bool flg = regex_match(strDir.c_str(), regex(STR_REGEX_DIR));
    if (!flg || strDir.size() >= MAX_PATH)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    if (0 != remove(strDir.c_str()))
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }
#endif

    status = VCA_SUCCESSED;

finish:
    return status;
}

#ifdef __linux__
//! get current user path (only in linux defined)
/*!
    \userPath : get the current user path in linux
*/
void VcaGetUserPath(OUT string &userPath)
{
    struct passwd *pw;
    //get current user path
    pw = getpwuid(getuid());
    userPath = string(pw->pw_dir);
}
#endif

//! get the current path
/*!
    \path : output path of current module whose style is UNIX style
*/
VCA_EXECUTION_STATUS GetCurPath(OUT string &path)
{
    VCA_EXECUTION_STATUS status = VCA_FAILED;

#ifdef _WIN32
    char pathTmp[MAX_PATH]   = { 0 };
    char szFull[_MAX_PATH]   = { 0 };
    char szDrive[_MAX_DRIVE] = { 0 };
    char szDir[_MAX_DIR]     = { 0 };

    DWORD len = GetModuleFileNameA(NULL, szFull, sizeof(szFull) / sizeof(char));
    if (len <= 0)
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }
    _splitpath(szFull, szDrive, szDir, NULL, NULL);
    strcpy(pathTmp, szDrive);
    strcat(pathTmp, szDir);
    path = string(pathTmp);
    path = path.substr(0, path.rfind('\\'));
    for (auto it=path.begin(); it!=path.end(); ++it)
    {
        if ('\\' == *it) *it = '/';
    }
#else if defined __linux__
    char pathTmp[MAX_PATH];
    int cnt = readlink("/proc/self/exe", pathTmp, MAX_PATH);
    if(cnt < 0|| cnt >= MAX_PATH)
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }

    for(int i = cnt; i >= 0; --i)
    {
        if(pathTmp[i]=='/')
        {
            pathTmp[i + 1]='\0';
            break;
        }
    }

    path = string(pathTmp);
    path = path.substr(0, path.rfind('/'));
#endif

    status = VCA_SUCCESSED;

finish:
    return status;
}

//! get the config file absolute path
/*!
    \strCfgPath : input relative path of the config file
    \strPath    : output absolute path of the config file
*/
VCA_EXECUTION_STATUS GetConfigFilePath(
    IN  const char* const strCfgPath,
    OUT string            &strPath)
{
    VCA_EXECUTION_STATUS status = VCA_FAILED;

    string szPath;
    status = GetCurPath(szPath);
    if (VCA_SUCCESSED != status)
    {
        status = VCA_FAILED_UNKNOWN;
        goto finish;
    }

    strPath = szPath + '/';
    strPath += strCfgPath;

    status = VCA_SUCCESSED;

finish:
    return status;
}

//! split file absolute path into dir/name/ext
/*!
    \filePath : input path of the file
    \fileDir  : output directory of the file
    \fileName : output name of the file
    \fileExt  : output suffix of the file
*/
VCA_EXECUTION_STATUS SplitFilePath(
    IN  const string &filePath,
    OUT       string &fileDir,
    OUT       string &fileName,
    OUT       string &fileExt)
{
    VCA_EXECUTION_STATUS status = VCA_FAILED;
    size_t posDot, posSlash;

    bool flg = regex_match(filePath.c_str(), regex(STR_REGEX_PATH));
    if (!flg || filePath.size() >= MAX_PATH)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

#ifdef _WIN32
    posDot   = filePath.find_last_of('.');
    posSlash = filePath.find_last_of('/');
    if (posDot == string::npos || posSlash == string::npos || posDot <= posSlash)
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    fileDir  = filePath.substr(0, posSlash);
    fileName = filePath.substr(posSlash + 1, posDot - posSlash - 1);
    fileExt  = filePath.substr(posDot + 1);
#else if defined __linux__
    posDot   = filePath.find_last_of('.');
    posSlash = filePath.find_last_of('/');
    if (posSlash == string::npos) // if path contains no slash, it must be error
    {
        status = VCA_INVALID_INPUT_ARGS;
        goto finish;
    }

    if (posDot != string::npos) // if path contains a dot
    {
        if (posDot < posSlash) // dir contains dots and file has no suffix
        {
            fileDir = filePath.substr(0, posSlash);
            fileName = filePath.substr(posSlash + 1);
            fileExt = string();
        }
        else if (posDot > posSlash) // file has the suffix, the same as windows
        {
            fileDir = filePath.substr(0, posSlash);
            fileName = filePath.substr(posSlash + 1, posDot - posSlash - 1);
            fileExt = filePath.substr(posDot + 1);
        }
        else
        {
            status = VCA_INVALID_INPUT_ARGS;
            goto finish;
        }
    }
    else // path contains no dot and file has no suffix
    {
        fileDir = filePath.substr(0, posSlash);
        fileName = filePath.substr(posSlash + 1);
        fileExt = string();
    }
#endif

    status = VCA_SUCCESSED;

finish:
    return status;
}

//! read all the content of the input file into a string
//  note: the point to the output string returned must be freed after used
/*!
    \filePath : input path of the input file
*/
char* ReadStringFromFile(IN const char* const filePath)
{
    char* buffer = NULL;

    if (NULL != filePath)
    {
        ifstream infile(filePath, ifstream::binary);
        if (!infile.is_open())
        {
            printf_s("cannot open filePath=%s\n", filePath);
            goto finish;
        }

        infile.seekg(0, infile.end);
        streamsize size = infile.tellg();
        infile.seekg(0);

        // allocate memory for file content
        buffer = new(nothrow) char[static_cast<unsigned int>(size)];
        if (NULL == buffer)
        {
            goto finish;
        }

        // read content of infile
        infile.read(buffer, size);
    }

finish:
    return buffer;
}

//! remove the invalid characters(space, \t, \r, \n) at the end of the string
/*!
    \s : input string
*/
void RemoveLastInvalidCharacters(IN OUT string &s)
{
    size_t n = s.find_last_not_of(" \r\n\t");
    if (n != string::npos)
    {
        s.erase(n + 1, s.size() - n);
    }
}

//! read all the lines of the input file into a string vector (one element of the vector is one single line)
//  and remove all the invalid characters(space, \t, \r, \n) at the end of the line
/*!
    \filePath : input path of the input file
*/
vector<string> ReadFileIntoString(IN const char* const filePath)
{
    ifstream ifile(filePath);

    string s;
    vector<string> vstr;
    while (getline(ifile, s))
    {
        RemoveLastInvalidCharacters(s);
        vstr.push_back(s);
    }

    return vstr;
}

