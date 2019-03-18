#include "IWriteLog01.h"
#include "writeLog01.h"

INTERFACE_CLASS IWriteLog01* CreateWriteLog01()
{
    IWriteLog01 *pIWriteLog01 = new(CWriteLog01);
    return pIWriteLog01;
}

//!destroy a object, free the memory
INTERFACE_CLASS void DeleteWriteLog01(IN OUT IWriteLog01** const pIWriteLog01)
{
    CWriteLog01 *pCWriteLog01 = dynamic_cast<CWriteLog01*>(*pIWriteLog01);
    delete(pCWriteLog01);
    *pIWriteLog01 = NULL;
}
