//
// Generated by dtk
// Translation Unit: d_resorce.cpp
//

#include "d_resorce.h"
#include "dolphin/types.h"

/* 8006D804-8006D824       .text __ct__11dRes_info_cFv */
dRes_info_c::dRes_info_c()
    : mCount(0)
    , mpDMCommand(NULL)
    , mpArchive(NULL)
    , mpParentHeap(NULL)
    , mpDataHeap(NULL)
    , mpRes(NULL)
{
}

/* 8006D824-8006D8F4       .text __dt__11dRes_info_cFv */
dRes_info_c::~dRes_info_c() {
    if (mpDMCommand != NULL) {
        delete mpDMCommand;
        mpDMCommand = NULL;
    } else if (mpArchive != NULL) {
        deleteArchiveRes();
        if (mpDataHeap != NULL) {
            mDoExt_destroySolidHeap(mpDataHeap);
            mpDataHeap = NULL;
            mpArchive->unmount();
        }
        mpRes = NULL;
        mpArchive = NULL;
    }
}

/* 8006D8F4-8006D990       .text set__11dRes_info_cFPCcPCcUcP7JKRHeap */
int dRes_info_c::set(char const* pArcName, char const* pArcPath, u8 param_2, JKRHeap* pHeap) {
    char path[40];

    if (*pArcPath != NULL) {
        snprintf(path, 40, "%s%s.arc", pArcPath, pArcName);
        mDMCommand = mDoDvdThd_mountArchive_c::create(path, param_2, pHeap);

        if (mDMCommand == NULL) {
            return false;
        }
    }
    strncpy(mArchiveName, pArcName, 10);
    return true;
}

/* 8006D990-8006DCEC       .text setToonTex__FP12J3DModelData */
static void setToonTex(J3DModelData* pModel) {
    /* Nonmatching */
}

/* 8006DCEC-8006DFD4       .text setToonTex__FP16J3DMaterialTable */
static void setToonTex(J3DMaterialTable* pMaterial) {
    /* Nonmatching */
}

/* 8006DFD4-8006E7A4       .text loadResource__11dRes_info_cFv */
void dRes_info_c::loadResource() {
    /* Nonmatching */
}

/* 8006E7A4-8006E7EC       .text __dt__13JKRFileFinderFv */
JKRFileFinder::~JKRFileFinder() {
    /* Nonmatching */
}

/* 8006E7EC-8006E858       .text __dt__18J3DAnmTransformKeyFv */
J3DAnmTransformKey::~J3DAnmTransformKey() {
    /* Nonmatching */
}

/* 8006E858-8006E8B4       .text __dt__15J3DAnmTransformFv */
J3DAnmTransform::~J3DAnmTransform() {
    /* Nonmatching */
}

/* 8006E8B4-8006E8FC       .text __dt__10J3DAnmBaseFv */
J3DAnmBase::~J3DAnmBase() {
    /* Nonmatching */
}

/* 8006E8FC-8006EBD0       .text setRes__11dRes_info_cFv */
int dRes_info_c::setRes() {
    if (mpArchive == NULL) {
        if (mpDMCommand == NULL) {
            return -1;
        }
        if ((int)mpDMCommand->mIsDone == 0) {
            return 1;
        }

        mpArchive = mpDMCommand->getArchive();
        mpParentHeap = mpDMCommand->getHeap();

        delete mpDMCommand;
        mpDMCommand = NULL;

        if (mpArchive == NULL) {
            OSReport_Error("<%s.arc> setRes: archive mount error !!\n", mArchiveName);
            return -1;
        }
        if (mpParentHeap != NULL) {
            mpParentHeap->lock();
            mpDataHeap = mDoExt_createSolidHeapToCurrent(0, mpParentHeap, 0x20);

            int rt = loadResource();
            mDoExt_restoreCurrentHeap();
            mDoExt_adjustSolidHeap(mpDataHeap);
            heap->unlock();

            if (rt < 0) {
                return -1;
            }
        } else {
            mpDataHeap = mDoExt_createSolidHeapFromGameToCurrent(0, 0);
            if (mpDataHeap == NULL) {
                OSReport_Error("<%s.arc> mDMCommandsetRes: can't alloc memory\n", mArchiveName);
                return -1;
            }
            int rt = loadResource();
            mDoExt_restoreCurrentHeap();
            mDoExt_adjustSolidHeap(mpDataHeap);

            if (rt < 0) {
                return -1;
            }
        }

        u32 heapSize = mpDataHeap->getHeapSize();
        void* heapStartAddr = mpDataHeap->getStartAddr();
        DCStoreRangeNoSync(heapStartAddr, heapSize);
    }

    return 0;
}

/* 8006EBD0-8006EBF8       .text getArcHeader__FP10JKRArchive */
static SArcHeader* getArcHeader(JKRArchive* pArchive) {
    if (pArchive != NULL) {
        switch (pArchive->getMountMode()) {
        case JKRArchive::MOUNT_MEM:
            return ((JKRMemArchive*)pArchive)->getArcHeader();
        }
    }

    return NULL;
}

/* 8006EBF8-8006ECF4       .text dump_long__11dRes_info_cFP11dRes_info_ci */
void dRes_info_c::dump_long(dRes_info_c*, int) {
    /* Nonmatching */
}

/* 8006ECF4-8006EE6C       .text dump__11dRes_info_cFP11dRes_info_ci */
void dRes_info_c::dump(dRes_info_c*, int) {
    /* Nonmatching */
}

/* 8006EE6C-8006EF34       .text __dt__14dRes_control_cFv */
dRes_control_c::~dRes_control_c() {
    /* Nonmatching */
}

/* 8006EF34-8006F01C       .text setRes__14dRes_control_cFPCcP11dRes_info_ciPCcUcP7JKRHeap */
void dRes_control_c::setRes(const char*, dRes_info_c*, int, const char*, unsigned char, JKRHeap*) {
    /* Nonmatching */
}

/* 8006F01C-8006F074       .text syncRes__14dRes_control_cFPCcP11dRes_info_ci */
int dRes_control_c::syncRes(char const* arcName, dRes_info_c* pInfo, int infoSize) {
    dRes_info_c* resInfo = getResInfo(arcName, pInfo, infoSize);

    if (resInfo == NULL) {
        return -1;
    } else {
        return resInfo->setRes();
    }
}

/* 8006F074-8006F0E8       .text deleteRes__14dRes_control_cFPCcP11dRes_info_ci */
int dRes_control_c::deleteRes(char const* arcName, dRes_info_c* pInfo, int infoSize) {
    dRes_info_c* resInfo = getResInfo(arcName, pInfo, infoSize);

    if (resInfo == NULL) {
        return 0;
    } else {
        if (resInfo->decCount() == 0) {
            resInfo->~dRes_info_c();
        }
        return 1;
    }
}

/* 8006F0E8-8006F164       .text getResInfo__14dRes_control_cFPCcP11dRes_info_ci */
dRes_info_c* dRes_control_c::getResInfo(char const* pArcName, dRes_info_c* pResInfo, int infoSize) {
    for (int i = 0; i < infoSize; i++) {
        if (pResInfo->getCount() != 0) {
            if (!stricmp(pArcName, pResInfo->getArchiveName())) {
                return pResInfo;
            }
        }
        pResInfo++;
    }
    return NULL;
}

/* 8006F164-8006F18C       .text newResInfo__14dRes_control_cFP11dRes_info_ci */
dRes_info_c* dRes_control_c::newResInfo(dRes_info_c* pResInfo, int infoSize) {
    for (int i = 0; i < infoSize; i++) {
        if (pResInfo->getCount() == 0) {
            return pResInfo;
        }
        pResInfo++;
    }
    return NULL;
}

/* 8006F18C-8006F208       .text getResInfoLoaded__14dRes_control_cFPCcP11dRes_info_ci */
dRes_info_c* dRes_control_c::getResInfoLoaded(char const* arcName, dRes_info_c* pResInfo,
                                              int infoSize) {
    dRes_info_c* resInfo = getResInfo(arcName, pResInfo, infoSize);

    if (resInfo == NULL) {
        resInfo = NULL;
    } else if (resInfo->getArchive() == NULL) {
        OSReport_Warning("<%s.arc> getRes: res during reading !!\n", arcName);
        resInfo = NULL;
    }
    return resInfo;
}

/* 8006F208-8006F298       .text getRes__14dRes_control_cFPCclP11dRes_info_ci */
void* dRes_control_c::getRes(char const* arcName, s32 resIdx, dRes_info_c* pInfo, int infoSize) {
    dRes_info_c* resInfo = getResInfoLoaded(arcName, pInfo, infoSize);

    if (resInfo == NULL) {
        return resInfo;
    }
    JKRArchive* archive = resInfo->getArchive();
    u32 fileCount = archive->countFile();

    if (resIdx >= (int)fileCount) {
        OSReport_Error("<%s.arc> getRes: res index over !! index=%d count=%d\n", arcName, resIdx,
                       fileCount);
        return NULL;
    }
    return resInfo->getRes(resIdx);
}

/* 8006F298-8006F34C       .text getRes__14dRes_control_cFPCcPCcP11dRes_info_ci */
void* dRes_control_c::getRes(char const* arcName, char const* resName, dRes_info_c* pInfo, int infoSize) {
    dRes_info_c* resInfo = getResInfoLoaded(arcName, pInfo, infoSize);

    if (resInfo == NULL) {
        return resInfo;
    }

    JKRArchive* archive = resInfo->getArchive();
    JKRArchive::SDIFileEntry* entry = archive->findNameResource(resName);

    if (entry != NULL) {
        return resInfo->getRes(entry - archive->mFiles);
    } else {
        return NULL;
    }
}

/* 8006F34C-8006F3BC       .text getIDRes__14dRes_control_cFPCcUsP11dRes_info_ci */
void* dRes_control_c::getIDRes(char const* arcName, u16 param_1, dRes_info_c* pInfo, int infoSize) {
    dRes_info_c* resInfo = getResInfoLoaded(arcName, pInfo, infoSize);

    if (resInfo == NULL) {
        return resInfo;
    }

    JKRArchive* archive = resInfo->getArchive();
    int index = mDoExt_resIDToIndex(archive, param_1);

    if (index < 0) {
        return 0;
    }

    return resInfo->getRes(index);
}

/* 8006F3BC-8006F430       .text syncAllRes__14dRes_control_cFP11dRes_info_ci */
int dRes_control_c::syncAllRes(dRes_info_c* pInfo, int infoSize) {
    for (int i = 0; i < infoSize; i++) {
        if (pInfo->getDMCommand() != NULL && pInfo->setRes() > 0) {
            return 1;
        }
        pInfo++;
    }
    return 0;
}

/* 8006F430-8006F500       .text setStageRes__14dRes_control_cFPCcP7JKRHeap */
int dRes_control_c::setStageRes(char const* arcName, JKRHeap* pHeap) {
    char path[20];
    snprintf(path, 20, "/res/Stage/%s/", dComIfGp_getStartStageName());
    return setRes(arcName, &mStageInfo[0], 0x40, path, 1, pHeap);
}

/* 8006F500-8006F580       .text dump__14dRes_control_cFv */
void dRes_control_c::dump() {
    JUTReportConsole_f("\ndRes_control_c::dump mObjectInfo\n");
    dRes_info_c::dump(&mObjectInfo[0], ARRAY_SIZE(mObjectInfo));
    dRes_info_c::dump_long(&mObjectInfo[0], ARRAY_SIZE(mObjectInfo));

    JUTReportConsole_f("\ndRes_control_c::dump mStageInfo\n");
    dRes_info_c::dump(&mStageInfo[0], ARRAY_SIZE(mStageInfo));
    dRes_info_c::dump_long(&mStageInfo[0], ARRAY_SIZE(mStageInfo));
}

/* 8006F580-8006F5FC       .text __dt__18mDoExt_transAnmBasFv */
mDoExt_transAnmBas::~mDoExt_transAnmBas() {
    /* Nonmatching */
}

/* 8006F5FC-8006F62C       .text getTransform__18J3DAnmTransformKeyCFUsP16J3DTransformInfo */
void J3DAnmTransformKey::getTransform(unsigned short, J3DTransformInfo*) const {
    /* Nonmatching */
}
