//
// Generated by dtk
// Translation Unit: m_Do_controller_pad.cpp
//

#include "m_Do/m_Do_controller_pad.h"
#include "SSystem/SComponent/c_API_controller_pad.h"
#include "SSystem/SComponent/c_lib.h"
#include "JSystem/JUtility/JUTGamePad.h"
#include "m_Do/m_Do_main.h"
#include "m_Do/m_Do_Reset.h"

JUTGamePad* g_mDoCPd_gamePad[4];
interface_of_controller_pad g_mDoCPd_cpadInfo[4];

inline void mDoCPd_ANALOG_CONV(u8 analog, f32& param_1) {
    param_1 = analog * (1.0f / 15.0f);
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

inline void mDoCPd_TRIGGER_CONV(u8 analog, f32& param_1) {
    param_1 = analog * 0.0071428571827709675f;
    if (param_1 > 1.0f) {
        param_1 = 1.0f;
    }
}

/* 80007598-800078C0       .text mDoCPd_Convert__FP27interface_of_controller_padP10JUTGamePad */
static s32 mDoCPd_Convert(interface_of_controller_pad* pInterface, JUTGamePad* pPad) {
    pInterface->mButtonFlags = pPad->getButton();
    pInterface->mMainStickPosX = pPad->getMainStickX();
    pInterface->mMainStickPosY = pPad->getMainStickY();
    pInterface->mMainStickValue = pPad->getMainStickValue();
    pInterface->mMainStickAngle = pPad->getMainStickAngle();
    pInterface->mCStickPosX = pPad->getSubStickX();
    pInterface->mCStickPosY = pPad->getSubStickY();
    pInterface->mCStickValue = pPad->getSubStickValue();
    pInterface->mCStickAngle = pPad->getSubStickAngle();

    mDoCPd_ANALOG_CONV(pPad->getAnalogA(), pInterface->mAnalogA);
    mDoCPd_ANALOG_CONV(pPad->getAnalogB(), pInterface->mAnalogB);
    mDoCPd_TRIGGER_CONV(pPad->getAnalogL(), pInterface->mTriggerLeft);
    mDoCPd_TRIGGER_CONV(pPad->getAnalogR(), pInterface->mTriggerRight);

    pInterface->mGamepadErrorFlags = pPad->getErrorStatus();
    return 1;
}

/* 800078C0-80007A70       .text mDoCPd_Read__Fv */
void mDoCPd_Read(void) {
    JUTGamePad::read();

    if (!mDoRst::isReset() && mDoRst::is3ButtonReset()) {
        JUTGamePad* pad = JUTGamePad::getGamePad(mDoRst::get3ButtonResetPort());

        if (!pad->isPushing3ButtonReset()) {
            mDoRst::off3ButtonReset();
        }
    }

    JUTGamePad** pad = g_mDoCPd_gamePad;
    interface_of_controller_pad* interface = g_mDoCPd_cpadInfo;

    for (u32 i = 0; i < 4; i++) {
        if (*pad == NULL) {
            cLib_memSet(interface, 0, sizeof(interface_of_controller_pad));
        } else {
            mDoCPd_Convert(interface, *pad);
        }

        pad++;
        interface++;
    }
    
    for (u32 i = 0; i < 4; i++) {
        g_mDoCPd_cpadInfo[i].mTrigLockL = false;
        g_mDoCPd_cpadInfo[i].mTrigLockR = false;
    }
}

/* 80007A70-80007BBC       .text mDoCPd_Create__Fv */
void mDoCPd_Create(void) {
    JUTGamePad::sSuppressPadReset = 1;

    JUTGamePad* pad = new JUTGamePad(JUTGamePad::Port_1);
    g_mDoCPd_gamePad[0] = pad;
    g_mDoCPd_gamePad[1] = NULL;

    if (mDoMain::developmentMode != 0) {
        g_mDoCPd_gamePad[2] = new JUTGamePad(JUTGamePad::Port_3);
        g_mDoCPd_gamePad[3] = new JUTGamePad(JUTGamePad::Port_4);
    } else {
        g_mDoCPd_gamePad[2] = NULL;
        g_mDoCPd_gamePad[3] = NULL;
    }

    JUTGamePad::setAnalogMode(3);
    if (!mDoRst::isReset()) {
        JUTGamePad::clearResetOccurred();
        JUTGamePad::setResetCallback(mDoRst_resetCallBack, NULL);
    }

    // JUTGba::create();
    // mDoGaC_Initial();

    interface_of_controller_pad* cpad = &g_mDoCPd_cpadInfo[0];
    for (int i = 0; i < 4; i++) {
        cpad->mTrigLockL = false;
        cpad->mHoldLockL = false;
        cpad->mTrigLockR = false;
        cpad->mHoldLockR = false;
        cpad++;
    }
}
