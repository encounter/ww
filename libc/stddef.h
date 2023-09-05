#ifndef _STDDEF_H_
#define _STDDEF_H_

#ifdef __cplusplus
extern "C" {
#endif

#define offsetof(type, member) ((size_t) & (((type*)0)->member))

typedef unsigned long size_t;
typedef long ptrdiff_t;

#ifndef NULL
#define NULL 0L
#endif

#ifdef __cplusplus
}
#endif

#endif // _STDDEF_H_
