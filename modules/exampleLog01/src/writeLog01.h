#ifndef _WRITELOG01_H_
#define _WRITELOG01_H_

#include "IWriteLog01.h"
#include "vxlLog.h"

using namespace std;

class CWriteLog01 : public IWriteLog01
{
public:
    CWriteLog01();

    ~CWriteLog01();

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