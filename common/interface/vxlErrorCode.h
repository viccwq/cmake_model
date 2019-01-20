#ifndef _VXLERRORCODE_H_
#define _VXLERRORCODE_H_

#define VXL_ERROR_CODE_OFFSET     1

// error code
enum VXL_EXECUTION_STATUS
{
    VXL_SUCCESSED                      = 0,
    VXL_FAILED                         = VXL_ERROR_CODE_OFFSET,
    VXL_CALL_MODULE_ERROR,             // +0x01
    VXL_LOAD_FILE_ERROR,               // +0x02
    VXL_READ_COM_ERROR,                // +0x03
    VXL_INIT_GPU_ERROR,                // +0x04
    VXL_CALL_GPU_ERROR,                // +0x05
    VXL_INVALID_INPUT_ARGS,            // +0x06
    VXL_INVALID_INPUT_MEM,             // +0x07
    VXL_INVALID_CHANNEL_ID,
    VXL_INVALID_CALIBRATION_MODE,
    VXL_FAILED_UNKNOWN
};

#endif