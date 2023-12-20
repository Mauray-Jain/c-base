#ifndef BASE_CONSTANTS_H
#define BASE_CONSTANTS_H

#include "types.h"

static const i8  min_i8  = (i8) 0x80;
static const i16 min_i16 = (i16)0x8000;
static const i32 min_i32 = (i32)0x80000000;
static const i64 min_i64 = (i64)0x8000000000000000llu;

static const i8  max_i8  = (i8) 0x7f;
static const i16 max_i16 = (i16)0x7fff;
static const i32 max_i32 = (i32)0x7fffffff;
static const i64 max_i64 = (i64)0x7fffffffffffffffllu;

static const u8  max_u8  = 0xff;
static const u16 max_u16 = 0xffff;
static const u32 max_u32 = 0xffffffff;
static const u64 max_u64 = 0xffffffffffffffffllu;

static const f32 pi_f32 = 3.14159265359f;
static const f32 e_f32  = 2.71828182846f;
static const f64 pi_f64 = 3.14159265359;
static const f64 e_f64  = 2.71828182846;

#endif /* BASE_CONSTANTS_H */
