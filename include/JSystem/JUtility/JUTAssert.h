#ifndef JUTASSERT_H
#define JUTASSERT_H

#include "dolphin/types.h"

#if DEBUG
#define JUT_ASSERT(FILE, LINE, COND)                                                               \
    if (!(COND)) {                                                                                 \
        JUTAssertion::showAssert(JUTAssertion::getSDevice(), FILE, LINE, #COND);                   \
        OSPanic(FILE, LINE, "Halt");                                                               \
    }

#else
#define JUT_ASSERT(...)
#endif

#if DEBUG
#define JUT_PANIC(FILE, LINE, TEXT)                                                                \
    JUTAssertion::showAssert(JUTAssertion::getSDevice(), FILE, LINE, TEXT);                        \
    OSPanic(FILE, LINE, "Halt");

#else
#define JUT_PANIC(...)
#endif

namespace JUTAssertion {
void create();
u32 flush_subroutine();
void flushMessage();
void flushMessage_dbPrint();
void setVisible(bool);
void setMessageCount(int);

u32 getSDevice();
void showAssert(u32, const char*, int, const char*);
};  // namespace JUTAssertion

extern bool sAssertVisible;

#endif /* JUTASSERT_H */
