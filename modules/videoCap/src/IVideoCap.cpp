#include "IVideoCap.h"
#include "videoCap.h"

INTERFACE_CLASS IVideoCap* CreateVideoCap()
{
    IVideoCap *pIVideoCap = new(CVideoCap);
    return pIVideoCap;
}

//!destroy a object, free the memory
INTERFACE_CLASS void DeleteVideoCap(IN OUT IVideoCap** const pIVideoCap)
{
    CVideoCap *pCVideoCap = dynamic_cast<CVideoCap*>(*pIVideoCap);
    delete(pCVideoCap);
    *pIVideoCap = NULL;
}
