/**
 * f_op_overlap_mng.cpp
 * Overlap Process Manager
 */

#include "f_op/f_op_overlap_mng.h"
#include "SSystem/SComponent/c_request.h"
#include "f_op/f_op_overlap_req.h"
#include "f_op/f_op_scene_pause.h"
#include "f_pc/f_pc_executor.h"


// making it not an array put it in .bss
static request_base_class* l_fopOvlpM_overlap[1] = {NULL};

int fopOvlpM_SceneIsStop() {
    if (l_fopOvlpM_overlap[0]) {
        return fopScnPause_Enable(
            (scene_class*)fpcEx_SearchByID(l_fopOvlpM_overlap[0]->field_0x20[0x32]));
    } else {
        return 0;
    }
}

int fopOvlpM_SceneIsStart() {
    if (l_fopOvlpM_overlap[0]) {
        return fopScnPause_Disable(
            (scene_class*)fpcEx_SearchByID(l_fopOvlpM_overlap[0]->field_0x20[0x32]));
    } else {
        return 0;
    }
}

int fopOvlpM_IsOutReq(overlap_task_class* pTaskClass) {
    return (pTaskClass->field_0xc4 & 0x3F) == 2;
}

void fopOvlpM_Done(overlap_task_class* pTaskClass) {
    cReq_Done((request_base_class*)&pTaskClass->field_0xc4);
}

void fopOvlpM_ToldAboutID(unsigned int param_1) {
    l_fopOvlpM_overlap[0] ? l_fopOvlpM_overlap[0]->field_0x20[0x32] = param_1 : 0;
}

int fopOvlpM_IsPeek() {
    return l_fopOvlpM_overlap[0] ? l_fopOvlpM_overlap[0]->field_0x8 : 0;
}

int fopOvlpM_IsDone() {
    return l_fopOvlpM_overlap[0] ? cReq_Is_Done(l_fopOvlpM_overlap[0]) : 0;
}

int fopOvlpM_IsDoingReq() {
    if (l_fopOvlpM_overlap[0] && l_fopOvlpM_overlap[0]->field_0x4 == 1) {
        return 1;
    }

    return 0;
}

int fopOvlpM_ClearOfReq() {
    return l_fopOvlpM_overlap[0] ?
               fopOvlpReq_OverlapClr((overlap_request_class*)l_fopOvlpM_overlap[0]) :
               0;
}

static overlap_request_class l_fopOvlpM_Request;

request_base_class* fopOvlpM_Request(s16 param_1, u16 param_2) {
    if (!l_fopOvlpM_overlap[0]) {
        request_base_class* tmp = fopOvlpReq_Request(&l_fopOvlpM_Request, param_1, param_2);
        l_fopOvlpM_overlap[0] = tmp;
        return tmp;
    }

    return 0;
}

void fopOvlpM_Management() {
    if (l_fopOvlpM_overlap[0]) {
        int tmp = fopOvlpReq_Handler((overlap_request_class*)l_fopOvlpM_overlap[0]);
        if (6 <= tmp || 3 > tmp) {
            return;
        }
        l_fopOvlpM_overlap[0] = NULL;
    }
}

int fopOvlpM_Cancel() {
    if (!l_fopOvlpM_overlap[0]) {
        return 1;
    }

    if (fopOvlpReq_Cancel((overlap_request_class*)l_fopOvlpM_overlap[0]) == true) {
        l_fopOvlpM_overlap[0] = NULL;
        return 1;
    }

    return 0;
}

void fopOvlpM_Init() {}
