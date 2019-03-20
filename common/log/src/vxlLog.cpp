#include <iostream>
#include <stdarg.h>

#include "vxlLog.h"
#include "vxlMutex.h"
#include "vxlPortable.h"

#ifdef _WIN32
#define LOG_FILE_DIR  "C:/DebugLog"
#elif defined __linux__
#define LOG_FILE_DIR  "/DebugLog"
#endif
#define LOG_FILE_NAME "VIC_VXL"
#define LOG_FILE_EXT  ".txt"

#define LOG_DEBUG_PRNT        0 // default 0, to control whether to print log debug info or not
#define MAX_LOG_SIZE          (10 * 1024 * 1024)
#define MAX_STR_SIZE_INLINE   (1024)

FILE*         Logger::m_hLogFile  = NULL;
VXL_LOG_LEVEL Logger::m_logLevel  = VXL_LOG_LEVEL_DEFAULT;

std::string Logger::m_strFileDir  = LOG_FILE_DIR;
std::string Logger::m_strFileName = LOG_FILE_NAME;
std::string Logger::m_strFilePath = "";
bool Logger::m_bSetDir            = false;
bool Logger::m_bCreateDir         = true;

bool Logger::m_bEnableFileLog     = false;
int  Logger::m_logFileCount       = 0;
std::mutex   Logger::m_mutex;
static Logger* m_pLogger = NULL;

const char* m_logLevelStr[VXL_LOG_LEVEL_COUNT] = {
    "TRACE",
    "INFO",
    "WARNING",
    "ERROR",
    "FATAL",
    "NONE"
};

Logger::Logger()
{
}

Logger::~Logger()
{
#if LOG_DEBUG_PRNT
    printf("~Logger m_pLogger==========%p\n", m_pLogger);
#endif
    Logger::Dispose();
    if (m_pLogger != NULL)
    {
        delete m_pLogger;
        m_pLogger = NULL;
    }
}

Logger* Logger::Instance()
{
#if LOG_DEBUG_PRNT
    printf("Logger::Instance\n");
#endif
    CVxlLockGuard lock(Logger::m_mutex);
    if (m_pLogger == NULL)
    {
        m_pLogger = new(std::nothrow) Logger();
#if LOG_DEBUG_PRNT
        printf("new m_pLogger=%p\n", m_pLogger);
#endif
    }

    return m_pLogger;
}

void Logger::SetFileDirectory(
    IN const std::string &strFileDir,
    IN bool bDeleteOldDir)
{
    CVxlLockGuard lock(Logger::m_mutex);
    Logger::m_strFileDir = strFileDir;
    Logger::m_bSetDir = true;
}

void Logger::SetFileName(const std::string& strFileName)
{
    CVxlLockGuard lock(m_mutex);
    m_strFileName = strFileName;
    Logger::MakeLogFilePath();
}

void Logger::SetLevel(IN VXL_LOG_LEVEL logLevel)
{
    CVxlLockGuard lock(Logger::m_mutex);
    Logger::m_logLevel = logLevel;
}

void Logger::EnableFileLog(IN bool bEnableFileLog)
{
    CVxlLockGuard lock(Logger::m_mutex);
    Logger::m_bEnableFileLog = bEnableFileLog;
}

void Logger::Log(IN VXL_LOG_LEVEL logLevel, IN const char* const format, ...)
{
    CVxlLockGuard lock(Logger::m_mutex);

    int ret = 0;

    if (NULL == m_hLogFile && !Logger::Initialise())
    {
#if LOG_DEBUG_PRNT
        printf("Log return directly!\n");
#endif
        return;
    }

    char szBuffer[MAX_STR_SIZE_INLINE];

    va_list args;
    va_start(args, format);

    ret = 0;
    ret = _vsnprintf_s(szBuffer, MAX_STR_SIZE_INLINE-1, format, args);
    if (ret < 0)
    {
#if LOG_DEBUG_PRNT
        printf("_vsnprintf_s ret = %d!\n", ret);
#endif
        return;
    }

    va_end(args);

#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    ret = 0;
    ret = fprintf(m_hLogFile, "[%04u-%02u-%02u %02u:%02u:%02u:%03u] [%s] %s",
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, st.wMilliseconds,
        m_logLevelStr[logLevel], szBuffer);
#elif defined __linux__
    time_t st;
    struct tm *p = NULL;
    time(&st);
    p = localtime(&st);
    ret = 0;
    ret = fprintf(m_hLogFile, "[%04u-%02u-%02u %02u:%02u:%02u] [%s] %s",
        p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec,
        m_logLevelStr[logLevel], szBuffer);

    p = NULL;
#endif

    if (ret < 0)
    {
#if LOG_DEBUG_PRNT
        printf("fprintf ret = %d!\n", ret);
#endif
        Logger::Dispose();
    }
    else
    {
        fflush(m_hLogFile);

        if (ftell(m_hLogFile) >= MAX_LOG_SIZE)
        {
            m_logFileCount++;
            Logger::MakeLogFilePath();
        }
    }
}

bool Logger::Initialise()
{
    if (Logger::m_hLogFile != NULL)
    {
#if LOG_DEBUG_PRNT
        printf("Logger::m_hLogFile != NULL -> true\n");
#endif
        return true;
    }
    if (!Logger::m_bEnableFileLog)
    {
#if LOG_DEBUG_PRNT
        printf("!Logger::m_bEnableFileLog -> false\n");
#endif
        return false;
    }

    if (Logger::m_bCreateDir)
    {
        if (!Logger::m_bSetDir)
        {
#ifdef __linux__
            std::string userPth;
            VxlGetUserPath(userPth);
            m_strFileDir = userPth + m_strFileDir;
#if LOG_DEBUG_PRNT
            printf("m_strFileDir=%s\n", m_strFileDir.c_str());
#endif
#endif
        }
        if (!CreateFileDirectory(Logger::m_strFileDir))
        {
#if LOG_DEBUG_PRNT
            printf("!CreateFileDirectory(Logger::m_strFileDir) -> false\n");
#endif
            return false;
        }
        Logger::m_bCreateDir = false;
    }

#if LOG_DEBUG_PRNT
    printf("%s\n", Logger::m_strFilePath.c_str());
#endif
    Logger::m_hLogFile = fopen(Logger::m_strFilePath.c_str(), "w+");
    if (Logger::m_hLogFile == NULL)
    {
#if LOG_DEBUG_PRNT
        printf("Logger::m_hLogFile == NULL -> false\n");
#endif
        return false;
    }

    return true;
}

void Logger::Dispose()
{
#if LOG_DEBUG_PRNT
    printf("Logger::Dispose\n");
#endif
    if (NULL != Logger::m_hLogFile)
    {
        fflush(Logger::m_hLogFile);
        fclose(Logger::m_hLogFile);
        Logger::m_hLogFile = NULL;
    }
}

bool Logger::CreateFileDirectory(const std::string& strFileDir, bool bDeleteOldDir)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    std::string strDirTemp = strFileDir;
    if (strDirTemp.substr(strDirTemp.length() - 1, 1) == "/")
    {
        strDirTemp = strDirTemp.substr(0, strDirTemp.length() - 1);
    }

    status = CreateDir(strDirTemp);
    if (VXL_SUCCESSED != status)
    {
#if LOG_DEBUG_PRNT
        printf("!CreateLogDirectory(strDirTemp) -> false\n");
#endif
        return false;
    }

    if (bDeleteOldDir)
    {
        Dispose();
        status = DeleteDir(Logger::m_strFileDir);
        if (VXL_SUCCESSED != status)
        {
#if LOG_DEBUG_PRNT
            printf("DeleteDir(m_strFileDir=%s) failed! status=%d\n",
                Logger::m_strFileDir.c_str(), status);
#endif
            return false;
        }
    }

    Logger::m_strFileDir = strDirTemp;
    Logger::MakeLogFilePath();

    return true;
}

void Logger::MakeLogFilePath()
{
    char buf[128] = { 0 };

    Logger::Dispose();
    Logger::m_strFilePath  = Logger::m_strFileDir + "/";
    Logger::m_strFilePath += Logger::m_strFileName;

#ifdef _WIN32
    SYSTEMTIME st;
    GetLocalTime(&st);
    _snprintf_s(buf, sizeof(buf), "_%4d%02d%02d%02d%02d%02d_%d" LOG_FILE_EXT,
        st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond, Logger::m_logFileCount);
#elif defined __linux__
    time_t st(0);
    struct tm *p = NULL;
    time(&st);
    p = localtime(&st);
    snprintf(buf, sizeof(buf), "_%4d%02d%02d%02d%02d%02d_%d" LOG_FILE_EXT,
        p->tm_year, p->tm_mon, p->tm_mday, p->tm_hour, p->tm_min, p->tm_sec, Logger::m_logFileCount);

    p = NULL;
#endif
    Logger::m_strFilePath += buf;
}
