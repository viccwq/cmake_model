#include "vxlCmakeCfg.h"
#include "IDrawImg.h"

int main()
{
    char filePath[256];
    sprintf(filePath, "%s%s", VXL_TRUNK_DIR, "/data/Lighthouse.jpg");
    IDrawImg* pDrawImg = CreateDrawImg();
    pDrawImg->Init(filePath);
    pDrawImg->Process();
    pDrawImg->Release();
    DeleteDrawImg(&pDrawImg);
    return 0;
}
