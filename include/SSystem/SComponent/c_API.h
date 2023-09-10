#ifndef C_API_H
#define C_API_H

#include "dolphin/types.h"

typedef void (*cAPIGph_Mthd)(void);

struct cAPI_Interface {
    u8* graphicInfo;
    cAPIGph_Mthd create;
    cAPIGph_Mthd beforeOfDraw;
    cAPIGph_Mthd afterOfDraw;
    cAPIGph_Mthd painter;
    cAPIGph_Mthd blankingON;
    cAPIGph_Mthd blankingOFF;
    cAPIGph_Mthd unk0x1C;
};

extern cAPI_Interface g_cAPI_Interface;

#endif /* C_API_H */
