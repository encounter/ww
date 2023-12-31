//
// Generated by dtk
// Translation Unit: c_malloc.cpp
//

#include "SSystem/SComponent/c_malloc.h"
#include "JSystem/JKernel/JKRHeap.h"
#include "dolphin/types.h"

JKRHeap* cMl::Heap;

/* 802412F0-802412F8       .text init__3cMlFP7JKRHeap */
void cMl::init(JKRHeap* heap) {
    Heap = heap;
}

/* 802412F8-80241330       .text memalignB__3cMlFiUl */
void* cMl::memalignB(int alignment, unsigned long size) {
    if (size == 0)
        return NULL;
    else
        return Heap->alloc(size, alignment);
}

/* 80241330-8024135C       .text free__3cMlFPv */
void cMl::free(void* ptr) {
    if (ptr != NULL)
        Heap->free(ptr);
}
