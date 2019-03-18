#ifndef _WRITELOG02_H_
#define _WRITELOG02_H_

#include "IWriteLog02.h"
#include "vxlLog.h"

using namespace std;

class CWriteLog02 : public IWriteLog02
{
public:
    CWriteLog02();

    ~CWriteLog02();

    void EnableLog(IN VXL_LOG_LEVEL logLevel = VXL_LOG_LEVEL_DEFAULT, IN const char* const logDir = NULL);

    void DisableLog();

    VXL_EXECUTION_STATUS Init(IN const char* fileName);

    VXL_EXECUTION_STATUS Release();

    VXL_EXECUTION_STATUS Process(IN const int frameCnt);

protected:
    string m_fileName;

private:
};

#endif