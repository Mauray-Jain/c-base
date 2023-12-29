#ifndef BASE_TYPES_H
#define BASE_TYPES_H

#include <stdint.h>
#include <stddef.h>

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef uint8_t   u8;
typedef uint16_t  u16;
typedef uint32_t  u32;
typedef uint64_t  u64;
typedef size_t    usize;
typedef uintptr_t uptr;

typedef float  f32;
typedef double f64;

// Compound types

typedef struct str8 {
	u8* str; // \0 terminated
	usize size; // Doesn't include \0 basically sizeof str
} str8;

typedef struct str8node {
	struct str8node* next;
	str8 string;
} str8node;

typedef struct str8list {
	str8node* first;
	str8node* last;
	usize node_count;
	usize total_size;
} str8list;

typedef struct utfdecode {
	u32 codepoint;
	usize size;
} utfdecode;

#define GENERATE_V2(T) \
typedef struct v2##T { \
	T x; \
	T y; \
} v2##T;

#define GENERATE_V3(T) \
typedef struct v3##T { \
	T x; \
	T y; \
	T z; \
} v3##T;

#define GENERATE_V4(T) \
typedef struct v4##T { \
	T x; \
	T y; \
	T z; \
	T w; \
} v4##T;

#define GENERATE_ARRAY(T) \
typedef struct arr##T { \
	T* vals; \
	size_t count; \
} arr##T

// Max isn't inclusive
#define GENERATE_RANGE(T) \
typedef struct range##T { \
	T min; \
	T max; \
} range##T;

GENERATE_V2(i32);
GENERATE_V2(f32);
GENERATE_V3(f32);
GENERATE_V4(f32);

GENERATE_ARRAY(u32);
GENERATE_ARRAY(f32);
GENERATE_ARRAY(v2i32);

GENERATE_RANGE(i32);

#endif /* BASE_TYPES_H */
