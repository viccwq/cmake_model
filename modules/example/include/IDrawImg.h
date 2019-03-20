#ifndef _IDRAWIMG_H_
#define _IDRAWIMG_H_

#include "vxlMacros.h"
#include "vxlErrorCode.h"
#include "vxlSysInc.h"

class IDrawImg
{
public:
    //! register the RuntimeExceptionCallback
    /*!
        \func    : function pointer to the runtime exception callback of the caller of this module
        \usrData : pointer to caller of this module
    */
    //virtual void RegisterRuntimeExceptionCallback(IN RuntimeStatusFunc func, IN void *usrData) = 0;

    //! launch log operation
    /*!
        after it called,program will output log information, such as,error information,etc.
    */
    //virtual void EnableLog(IN VCA_LOG_LEVEL logLevel = VCA_LOG_LEVEL_DEFAULT, IN const char* const logDir = NULL) = 0;

    //! cancel log operation
    /*!
        after it called,program will not output log information, such as,error information,etc.
    */
    virtual void DisableLog() = 0;

    //! init data, get rotated angle based on different coordinate system transform mode : world->camera; camera->world
    /*!
    */
    virtual VXL_EXECUTION_STATUS Init(IN const char* fileName) = 0;

    //! release resources
    virtual VXL_EXECUTION_STATUS Release() = 0;


    virtual VXL_EXECUTION_STATUS Process() = 0;
};

#ifdef _WIN32
#ifdef EXAMPLE_EXPORTS
#define INTERFACE_CLASS extern "C" __declspec(dllexport)
#else
#define INTERFACE_CLASS extern "C" __declspec(dllimport)
#endif
#elif defined __linux__
#define INTERFACE_CLASS __attribute__ ((visibility("default")))
#endif

//! creat a object
INTERFACE_CLASS IDrawImg* CreateDrawImg();

//!destroy a object, free the memory
INTERFACE_CLASS void DeleteDrawImg(IN OUT IDrawImg** const pIDrawImg);
#endif