#include "videoCap.h"

CVideoCap::CVideoCap()
{
    this->bIsInit           = false;
    this->bIsFirstCall      = true;
    this->pVideoCap         = NULL;
}

CVideoCap::~CVideoCap()
{

}

void CVideoCap::DisableLog()
{
    return;
}

VXL_EXECUTION_STATUS CVideoCap::Init(
    IN const VideoCapCfg  &cfg,
    IN const VideoCapPara &para)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

//    LogInfo(STR_CR(PLUSLINE(CMutatedFrameDetect::Init() begin FMT_POINTu(id))), this->detectCfg.id);
    VideoCapCfgInternal  videoCapCfgTmp;
    VideoCapParaInternal videoCapParaTmp;

    if (this->bIsInit)
    {
        status = VXL_CALL_MODULE_ERROR;
        //LogError(STR_CR(CMutatedFrameDetect has been inited!));
        goto finish;
    }

    videoCapCfgTmp.Load(cfg);
    videoCapParaTmp.Load(para);

//     cv::Size size(1092, 1080);   // 1080p
//     cv::Size size(1280, 720);    // 720p
//     cv::Size size(720, 480);     // DV
//     cv::Size size(640, 480);     //4:3
//     cv::Size size(1280, 960);    //4:3

    status = this->__SetCfg(videoCapCfgTmp);
    status = this->__SetPara(videoCapParaTmp);

    status = this->__InitCap();

    this->bIsInit = true;

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CVideoCap::Release()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    if (!this->bIsInit)
    {
        status = VXL_CALL_MODULE_ERROR;
        goto finish;
    }

    this->__ReleaseCap();

    this->bIsInit = false;

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CVideoCap::Process(IN OUT char *imgBuff, IN const VxlSize &vxlSize)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;
    cv::Mat frame;
    if (!this->bIsInit)
    {
        status = VXL_CALL_MODULE_ERROR;
        goto finish;
    }

    cv::Size size(vxlSize.width, vxlSize.height);
    frame = cv::Mat(size, CV_8UC3, imgBuff);
    this->pVideoCap->read(frame);

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CVideoCap::SetPara(
    IN const VideoCapPara &para)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    //    LogInfo(STR_CR(PLUSLINE(CMutatedFrameDetect::Init() begin FMT_POINTu(id))), this->detectCfg.id);
    VideoCapParaInternal videoCapParaTmp;

    if (this->bIsInit)
    {
        status = VXL_CALL_MODULE_ERROR;
        //LogError(STR_CR(CMutatedFrameDetect has been inited!));
        goto finish;
    }

    videoCapParaTmp.Load(para);

    status = this->__SetPara(videoCapParaTmp);

    status = VXL_SUCCESSED;
finish:

    return status;
}


VXL_EXECUTION_STATUS CVideoCap::__InitCap()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    this->pVideoCap = new cv::VideoCapture;
    //open the video
    this->pVideoCap->open(0);
    //check if we succeeded
    if (!this->pVideoCap->isOpened())
    {
        status = VXL_FAILED;
        this->pVideoCap->release();
        goto finish;
    }
    //http://www.ihalcon.com/read-6985.html
    std::cout << " Width=" << this->pVideoCap->get(CV_CAP_PROP_FRAME_WIDTH) <<
        " Height=" << this->pVideoCap->get(CV_CAP_PROP_FRAME_HEIGHT) <<
        " FOCUS=" << this->pVideoCap->get(CV_CAP_PROP_FOCUS) <<
        " FOURCC=" << this->pVideoCap->get(CV_CAP_PROP_FOURCC) << std::endl;

    std::cout << this->pVideoCap->set(CV_CAP_PROP_FRAME_WIDTH, this->videoCapCfgInternal.capSize.width) << std::endl;
    std::cout << this->pVideoCap->set(CV_CAP_PROP_FRAME_HEIGHT, this->videoCapCfgInternal.capSize.height) << std::endl;
    if (this->videoCapCfgInternal.capFocus < 1e-3)
    {
        std::cout << this->pVideoCap->set(CV_CAP_PROP_AUTOFOCUS, 250.0) << std::endl;
    }
    else 
    {
        std::cout << this->pVideoCap->set(CV_CAP_PROP_FOCUS, this->videoCapCfgInternal.capFocus) << std::endl;
    }
    std::cout << this->pVideoCap->set(CV_CAP_PROP_FOURCC, CV_FOURCC('M', 'J', 'P', 'G')) << std::endl;

    std::cout << " Width=" << this->pVideoCap->get(CV_CAP_PROP_FRAME_WIDTH) <<
        " Height=" << this->pVideoCap->get(CV_CAP_PROP_FRAME_HEIGHT) <<
        " FOCUS=" << this->pVideoCap->get(CV_CAP_PROP_FOCUS) <<
        " FOURCC=" << this->pVideoCap->get(CV_CAP_PROP_FOURCC) << std::endl;

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS  CVideoCap::__ReleaseCap()
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;

    if (this->pVideoCap)
    {
        this->pVideoCap->release();
    }

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CVideoCap::__SetCfg(
    IN const VideoCapCfgInternal &cfgInternal)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;
    //check the range of the cfg
    cfgInternal.CopyTo(this->videoCapCfgInternal);

    this->videoCapCfgInternal.Log();

    //apply the cfgs to the members

    status = VXL_SUCCESSED;
finish:

    return status;
}

VXL_EXECUTION_STATUS CVideoCap::__SetPara(
    IN const VideoCapParaInternal &paraInternal)
{
    VXL_EXECUTION_STATUS status = VXL_FAILED;
    //check the range of the para
    paraInternal.CopyTo(this->videoCaParaInternal);

    this->videoCaParaInternal.Log();

    //apply the paras to the members
    if (NULL != this->pVideoCap && this->pVideoCap->isOpened())
    {
        if (this->videoCaParaInternal.capFocus < 1e-3)
        {
            std::cout << this->pVideoCap->set(CV_CAP_PROP_AUTOFOCUS, 250.0) << std::endl;
        }
        else
        {
            std::cout << this->pVideoCap->set(CV_CAP_PROP_FOCUS, this->videoCaParaInternal.capFocus) << std::endl;
        }
    }

    status = VXL_SUCCESSED;
finish:

    return status;
}

