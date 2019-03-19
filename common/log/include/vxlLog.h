#ifndef __VXLLOG_H__
#define __VXLLOG_H__

#include <string>
#include <mutex>

#include "vxlLogAux.h"
#include "vxlMacros.h"

#ifdef _WIN32
#ifdef LOG_EXPORTS
#define INTERFACE_DLL __declspec(dllexport)
#else
#define INTERFACE_DLL __declspec(dllimport)
#endif
#else if defined __linux__
#define INTERFACE_CLASS __attribute__ ((visibility("default")))
#endif

#define LogTrace(fmt, ...)   if((Logger::m_logLevel <= VXL_LOG_TRACE) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VXL_LOG_TRACE, fmt, ##__VA_ARGS__);}
#define LogInfo(fmt, ...)    if((Logger::m_logLevel <= VXL_LOG_INFO) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VXL_LOG_INFO, fmt, ##__VA_ARGS__);}
#define LogWarning(fmt, ...) if((Logger::m_logLevel <= VXL_LOG_WARNING) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VXL_LOG_WARNING, fmt, ##__VA_ARGS__);}
#define LogError(fmt, ...)   if((Logger::m_logLevel <= VXL_LOG_ERROR) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VXL_LOG_ERROR, fmt, ##__VA_ARGS__);}
#define LogFatal(fmt, ...)   if((Logger::m_logLevel <= VXL_LOG_FATAL) && Logger::m_bEnableFileLog){Logger::Instance()->Log(VXL_LOG_FATAL, fmt, ##__VA_ARGS__);}
#define SetLogFileDirectory  Logger::SetFileDirectory
#define SetLogFileName       Logger::SetFileName
#define SetLogLevel          Logger::SetLevel
#define EnableLogFile        Logger::EnableFileLog

#define VXLEnableLog(logDir, logName, logLevel)                  \
    if(NULL!=logDir){SetLogFileDirectory(logDir);}               \
    SetLogFileName(logName);                                     \
    SetLogLevel(logLevel);                                       \
    EnableLogFile(true);

#define VXLDisableLog()                                          \
    EnableLogFile(false);

#ifdef _WIN32
#pragma warning(push)
#pragma warning(disable:4251)
#else if defined __linux__
//
#endif
//your declarations that cause 4251
class INTERFACE_DLL Logger
{
private:
    Logger();
public:
    virtual ~Logger();

    static Logger *Instance();
    static void SetFileDirectory(IN const std::string &strFileDir, IN bool bDeleteOldDir = false);
    static void SetFileName(const std::string &strFileName);
    static void SetLevel(IN VXL_LOG_LEVEL logLevel);
    static void EnableFileLog(IN bool bEnableFileLog);
    void Log(IN VXL_LOG_LEVEL logLevel, IN const char *const format, ...);

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
    static VXL_LOG_LEVEL m_logLevel;
};
#ifdef _WIN32
#pragma warning(pop)
#else if defined __linux__
//
#endif

#endif
