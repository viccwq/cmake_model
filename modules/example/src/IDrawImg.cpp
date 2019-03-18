#include "IDrawImg.h"
#include "drawImg.h"

INTERFACE_CLASS IDrawImg* CreateDrawImg()
{
    IDrawImg *pIDrawImg = new(CDrawImg);
    return pIDrawImg;
}

//!destroy a object, free the memory
INTERFACE_CLASS void DeleteDrawImg(IN OUT IDrawImg** const pIDrawImg)
{
    CDrawImg *pCDrawImg = dynamic_cast<CDrawImg*>(*pIDrawImg);
    delete(pCDrawImg);
    *pIDrawImg = NULL;
}
