#include "drawImg.h"

CDrawImg::CDrawImg()
{

}

CDrawImg::~CDrawImg()
{

}

void CDrawImg::DisableLog()
{
    return;
}

VXL_EXECUTION_STATUS CDrawImg::Init(IN const char* fileName)
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

VXL_EXECUTION_STATUS CDrawImg::Release()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;



    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CDrawImg::Process()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    cout<<"image path is:"<<m_fileName.c_str()<<endl;

    status = VXL_SUCCESSED;
finish:

    return status;
}
