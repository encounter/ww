//
// Generated by dtk
// Translation Unit: c_request.cpp
//

#include "SSystem/SComponent/c_request.h"
#include "dolphin/types.h"

/* 80245364-80245390       .text cReq_Is_Done__FP18request_base_class */
int cReq_Is_Done(request_base_class* param_0) {
    if (param_0->field_0x0.flag1 == 1) {
        param_0->field_0x0.flag1 = 0;
        return 1;
    }
    return 0;
}

/* 80245390-802453C0       .text cReq_Done__FP18request_base_class */
void cReq_Done(request_base_class* param_0) {
    param_0->field_0x0.flag0 = 0;
    param_0->field_0x0.flag1 = 1;
    param_0->field_0x0.flag2 = 0;
}


/* 802453C0-802453E0       .text cReq_Command__FP18request_base_classUc */
void cReq_Command(request_base_class* param_0, u8 param_1) {
    cReq_Create(param_0, param_1);
}

/* 802453E0-80245410       .text cReq_Create__FP18request_base_classUc */
void cReq_Create(request_base_class* param_0, u8 param_1) {
    param_0->field_0x0.flag0 = 1;
    param_0->field_0x0.flag1 = 0;
    param_0->field_0x0.flag2 = param_1;
}
