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

#define KB(x) ( (x) << 10 )
#define MB(x) ( (x) << 20 )
#define GB(x) ( (x) << 30 )
#define TB(x) ( (u64)(x) << 40llu )

#define AlignUpPow2(x, p) (((x) + (p) - 1)&~((p) - 1))
#define AlignDownPow2(x, p) ((x)&~((p) - 1))
#define IsPow2OrZero(x) ( ((x)&((x) - 1)) == 0 )

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

// Doubly Linked Lists
// f = first, l = last, n = node to be inserted
#define DLLPushBack_NP(f, l, n, next, prev) ( ((f) == 0)? \
( (f) = (l) = (n), (n)->next = (n)->prev = 0 ): \
( (n)->prev = (l), (l)->next = (n), (l) = (n), (n)->next = 0 ) \
)
#define DLLPushBack(f, l, n)  DLLPushBack_NP(f, l, n, next, prev)
#define DLLPushFront(f, l, n) DLLPushBack_NP(l, f, n, prev, next)
// f = first, l = last, n = node to be removed
#define DLLRemove_NP(f, l, n, next, prev) ( ((f) == (n))? \
( ((f) == (l))? ( (f) = (l) = 0 ): ( (f) = (f)->next, (f)->prev = 0 ) ): \
( ((l) == (n))? ( (l) = (l)->prev, (l)->next = 0 ): ( (n)->prev->next = (n)->next, (n)->next->prev = (n)->prev ) ) \
)
#define DLLRemove(f, l, n)  DLLRemove_NP(f, l, n, next, prev)

// Singly Linked List
#define SLLQueueEnqueue_N(f, n, next) ((n)->next = (f), (f) = (n))
#define SLLQueueEnqueue(f, n) SLLQueueEnqueue_N(f, n, next)
#define SLLQueueDequeue_N(f, next) ( ((f) == 0)? 0: ((f) = (f)->next) )
#define SLLQueueDequeue(f, n) SLLQueueDequeue_N(f, n, next)

#define SLLStackPush_N(f, l, n, next) ( ((f) == 0)? ((f) = (l) = (n), (n)->next = 0): ((l)->next = (n), (l) = (n), (n)->next = 0) )
#define SLLStackPush(f, l, n) SLLStackPush_N(f, l, n, next)
#define SLLStackPushFront_N(f, l, n, next) ( ((f) == 0)? ((f) = (l) = (n), (n)->next = 0): ((n)->next = (f), (f) = (n)) )
#define SLLStackPushFront(f, l) SLLStackPushFront_N(f, l, next)
#define SLLStackPop_N(f, l, next) ( ((f) == (l))? ((f) = (l) = 0): ((f) = (f)->next) )
#define SLLStackPop(f, l) SLLStackPop_N(f, l, next)

#endif /* BASE_MACROS_H */
