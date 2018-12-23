#ifndef _DRAWIMG_H_
#define _DRAWIMG_H_

#include "IDrawImg.h"

using namespace std;

class CDrawImg : public IDrawImg
{
public:
    CDrawImg();

    ~CDrawImg();

    void DisableLog();

    VXL_EXECUTION_STATUS Init(IN const char* fileName);

    VXL_EXECUTION_STATUS Release();

    VXL_EXECUTION_STATUS Process();

protected:
    string m_fileName;

private:
};

#endif