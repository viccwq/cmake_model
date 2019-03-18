#include "writeLog02.h"

CWriteLog02::CWriteLog02()
{

}

CWriteLog02::~CWriteLog02()
{

}

void CWriteLog02::EnableLog(IN VXL_LOG_LEVEL logLevel, IN const char* const logDir)
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

void CWriteLog02::DisableLog()
{
    EnableLogFile(false);
    return;
}

VXL_EXECUTION_STATUS CWriteLog02::Init(IN const char* fileName)
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

VXL_EXECUTION_STATUS CWriteLog02::Release()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;



    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CWriteLog02::Process(IN const int frameCnt)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    LogWarning("example log 02, %d\n", frameCnt);

    status = VXL_SUCCESSED;
finish:

    return status;
}
