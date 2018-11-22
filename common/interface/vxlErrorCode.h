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
    VXL_INVALID_COLORSPACE,            // +0x08
    VXL_INVALID_ANA_CAM_TYPE,          // +0x09
    VXL_INVALID_PTZ_CAM_TYPE,          // +0x0A
    VXL_INVALID_CHANNEL_ID,            // +0x0B
    VXL_INVALID_CALIBRATION_MODE,      // +0x0C
    VXL_INVALID_INTERPOLATION_MAP,     // +0x0D
    VXL_INVALID_LENS_CALIB_DATA,       // +0x0E
    VXL_INVALID_ANA_CAM_PARA,          // +0x0F
    VXL_INVALID_PTZ_CAM_PARA,          // +0x10
    VXL_EXCEED_PAN_RANGE,              // +0x11
    VXL_EXCEED_TILT_RANGE,             // +0x12
    VXL_INVALID_PAN,                   // +0x13
    VXL_INVALID_TILT,                  // +0x14
    VXL_UNDERFLOW_ZOOM,                // +0x15
    VXL_OVERFLOW_ZOOM,                 // +0x16
    VXL_EXCEED_PTZ_RANGE,              // +0x17
    VXL_INVALID_3D_POINT,              // +0x18,
    VXL_DEAD_ZONE_3D,                  // +0x19,
    VXL_RECT_OUT_OF_IMAGE,             // +0x1A,
    VXL_RECT_OUT_OF_BOTTOM_IMAGE,      // +0x1B,
    VXL_STUDENT_LOCATION_EXCEED_RANGE, // +0x1C,
    VXL_TEACHER_LOCATION_EXCEED_RANGE, // +0x1D,
    VXL_FAILED_UNKNOWN                 // +0x1E
};

#endif