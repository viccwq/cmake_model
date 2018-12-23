#include "IDrawImg.h"

int main()
{
    IDrawImg* pDrawImg = CreateDrawImg();
    pDrawImg->Init("../data/Lighthouse.jpg");
    pDrawImg->Process();
    pDrawImg->Release();

    return 0;
}