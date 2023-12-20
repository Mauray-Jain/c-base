#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#define Statement(s) do { s } while(0)

#if !defined (ENABLE_ASSERT)
#	define ENABLE_ASSERT 0
#endif

#if !defined (AssertBreak)
// The line below causes segfault on calling it
#define AssertBreak() ( *(volatile int*) 0 = 0 )
// #define AssertBreak() __builtin_trap()
#endif
#if !defined (AssertPrint)
#	include <stdio.h>
#	define AssertPrint() Statement( fprintf(stderr, "Assertion failed in %s on line %d\n", __FILE__, __LINE__); )
#endif

#if ENABLE_ASSERT
#	define Assert(c) Statement( if (!(c)) { AssertPrint(); AssertBreak(); } )
#else
#	define Assert(c)
#endif

#define Stringify_(s) #s
#define Stringify(s) Stringify_(s)
#define Concat_(a, b) a##b
#define Concat(a, b) Concat_(a, b)

#define ArrayLen(arr) ( sizeof(arr) / sizeof(*(arr)) )

// This generates a warning, may not standard compliant but works
#define IntFromPtr(p) ( (unsigned long long)((char*)(p) - (char*)0) )
#define PtrFromInt(n) ( (void*)((char*)0 + (n)) )

#define Member(T, m) (((T*)0)->m)
#define OffsetOfMember(T, m) IntFromPtr(&Member(T, m))

#define Min(a, b) (((a) > (b))? (b): (a))
#define Max(a, b) (((a) < (b))? (b): (a))
#define Clamp(a, x, b) (((x) < (a))? (a): (((b) < (x))? (b): (x)))

#include <string.h>

#define MemoryZero(p, z) memset((p), 0, (z))
#define MemoryZeroStruct(p) MemoryZero((p), sizeof(*(p)))
#define MemoryZeroArray(p) MemoryZero((p), sizeof(p))
#define MemoryZeroTyped(p, c) MemoryZero((p), sizeof(*(p)) * (c))

#define MemoryMatch(a, b, z) (memcmp((a), (b), (z)) == 0)

#define MemoryCopy(d, s, z) memmove((d), (s), (z))
#define MemoryCopyStruct(d, s) MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s))))
#define MemoryCopyArray(d, s) MemoryCopy((d), (s), Min(sizeof(d), sizeof(s)))
#define MemoryCopyTyped(d, s, c) MemoryCopy((d), (s), Min(sizeof(*(d)), sizeof(*(s)) * (c)))

#endif /* BASE_MACROS_H */
