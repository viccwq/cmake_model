#include "IWriteLog02.h"
#include "writeLog02.h"

INTERFACE_CLASS IWriteLog02* CreateWriteLog02()
{
    IWriteLog02 *pIWriteLog02 = new(CWriteLog02);
    return pIWriteLog02;
}

//!destroy a object, free the memory
INTERFACE_CLASS void DeleteWriteLog02(IN OUT IWriteLog02** const pIWriteLog02)
{
    CWriteLog02 *pCWriteLog02 = dynamic_cast<CWriteLog02*>(*pIWriteLog02);
    delete(pCWriteLog02);
    *pIWriteLog02 = NULL;
}
