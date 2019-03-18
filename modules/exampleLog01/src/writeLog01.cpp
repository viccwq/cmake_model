#include "writeLog01.h"

CWriteLog01::CWriteLog01()
{

}

CWriteLog01::~CWriteLog01()
{

}

void CWriteLog01::EnableLog(IN VXL_LOG_LEVEL logLevel, IN const char* const logDir)
{
#ifdef _WIN32
    SetLogFileDirectory("C:/DebugLog/Director");
#else if defined __linux__
    SetLogFileDirectory("./DebugLog/Director");
#endif
    //SetLogFileName(logDir);
    SetLogLevel(logLevel);
    EnableLogFile(true);
    return;
}

void CWriteLog01::DisableLog()
{
    EnableLogFile(false);
    return;
}

VXL_EXECUTION_STATUS CWriteLog01::Init(IN const char* fileName)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;
    if (NULL != fileName)
    {
        m_fileName = fileName;
    }
    else
    {
        status = VXL_FAILED_UNKNOWN;
        goto finish;
    }

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CWriteLog01::Release()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;



    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CWriteLog01::Process(IN const int frameCnt)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    LogWarning("example log 01, %d\n", frameCnt);

    status = VXL_SUCCESSED;
finish:

    return status;
}
