#ifndef _DRAWIMG_H_
#define _DRAWIMG_H_

#include "IDrawImg.h"

class CDrawImg : public IDrawImg
{
public:
    CDrawImg();

    ~CDrawImg();

    void DisableLog();

    VXL_EXECUTION_STATUS Init(const char* fileName);

    VXL_EXECUTION_STATUS Release();

    VXL_EXECUTION_STATUS Process();
protected:
private:
};

#endif