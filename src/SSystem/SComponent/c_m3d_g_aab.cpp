//
// Generated by dtk
// Translation Unit: c_m3d_g_aab.cpp
//

#include "SSystem/SComponent/c_m3d_g_aab.h"
#include "dolphin/types.h"

/* 80251CC4-80251D08       .text SetMinMax__8cM3dGAabFRC4cXyz */
void cM3dGAab::SetMinMax(const cXyz& pMinMax) {
    this->SetMin(pMinMax);
    this->SetMax(pMinMax);
}

/* 80251D08-80251D48       .text SetMin__8cM3dGAabFRC4cXyz */
void cM3dGAab::SetMin(const cXyz& pMin) {
    mMin.setMin(pMin);
}

/* 80251D48-80251D88       .text SetMax__8cM3dGAabFRC4cXyz */
void cM3dGAab::SetMax(const cXyz& pMax) {
    mMax.setMax(pMax);
}
