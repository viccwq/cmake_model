#ifndef __VXLLOG_H__
#define __VXLLOG_H__

#include <string>
#include <mutex>

#include "vxlLogAux.h"
#include "vxlMutex.h"
#include "vxlPortable.h"

#define LogTrace(fmt, ...)   if((Logger::m_logLevel <= VCA_LOG_TRACE) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VCA_LOG_TRACE, fmt, ##__VA_ARGS__);}
#define LogInfo(fmt, ...)    if((Logger::m_logLevel <= VCA_LOG_INFO) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VCA_LOG_INFO, fmt, ##__VA_ARGS__);}
#define LogWarning(fmt, ...) if((Logger::m_logLevel <= VCA_LOG_WARNING) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VCA_LOG_WARNING, fmt, ##__VA_ARGS__);}
#define LogError(fmt, ...)   if((Logger::m_logLevel <= VCA_LOG_ERROR) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VCA_LOG_ERROR, fmt, ##__VA_ARGS__);}
#define LogFatal(fmt, ...)   if((Logger::m_logLevel <= VCA_LOG_FATAL) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VCA_LOG_FATAL, fmt, ##__VA_ARGS__);}
#define SetLogFileDirectory  Logger::SetFileDirectory
#define SetLogFileName       Logger::SetFileName
#define SetLogLevel          Logger::SetLevel
#define EnableLogFile        Logger::EnableFileLog

#define VCAEnableLog(logDir, logName, logLevel)                  \
    if(NULL!=logDir){SetLogFileDirectory(logDir);}               \
    SetLogFileName(logName);                                     \
    SetLogLevel(logLevel);                                       \
    EnableLogFile(true);

#define VCADisableLog()                                          \
    EnableLogFile(false);

class Logger
{
private:
    Logger();
public:
    virtual ~Logger();

    static Logger *Instance();
    static void SetFileDirectory(IN const std::string &strFileDir, IN bool bDeleteOldDir = false);
    static void SetFileName(const std::string &strFileName);
    static void SetLevel(IN VCA_LOG_LEVEL logLevel);
    static void EnableFileLog(IN bool bEnableFileLog);
    void Log(IN VCA_LOG_LEVEL logLevel, IN const char *const format, ...);

private:
    Logger(Logger const &);
    Logger &operator=(Logger const &);

    static bool Initialise();
    static void Dispose();
    static bool CreateFileDirectory(const std::string &strFileDir, bool bDeleteOldDir = false);
    static void MakeLogFilePath();

    static FILE          *m_hLogFile;
    static bool          m_bSetDir;
    static bool          m_bCreateDir;

    static std::string   m_strFileDir;
    static std::string   m_strFileName;
    static std::string   m_strFilePath;

    static int           m_logFileCount;
    static std::mutex    m_mutex;

public:
    static bool          m_bEnableFileLog;
    static VCA_LOG_LEVEL m_logLevel;
};

#endif
