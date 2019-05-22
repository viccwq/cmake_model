#include <iostream>

#include "opencv2/opencv.hpp"
#include "vxlCmakeCfg.h"
#include "IVideoCap.h""

using namespace cv;

int main()
{
    VxlSize vxlSize(1280, 720);
    IVideoCap* pVideoCap = CreateVideoCap();
    VideoCapCfg  videoCapCfg;
    VideoCapPara videoCapPara;
    videoCapCfg.capSize = vxlSize;
    
    Mat img(vxlSize.height, vxlSize.width, CV_8UC3, Scalar(255.0, 255.0, 255.0));

    pVideoCap->Init(videoCapCfg, videoCapPara);
    for (int i = 0; i < 1000; i++)
    {
        pVideoCap->Process((char *)(img.data), vxlSize);
        imshow("frams", img);
        waitKey(30);
    }
    pVideoCap->Release();
    DeleteVideoCap(&pVideoCap);
    return 0;
}
