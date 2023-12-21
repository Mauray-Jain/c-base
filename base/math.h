#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "types.h"

static f32 inf_f32(void);
static f32 neg_inf_f32(void);

static f64 inf_f64(void);
static f64 neg_inf_f64(void);

// Math functions on float
static f32 sign_f32(f32 x);
static f64 sign_f64(f64 x);
static f32 abs_f32(f32 x);
static f64 abs_f64(f64 x);
static f32 sqrt_f32(f32 x);
static f32 sin_f32(f32 x);
static f32 cos_f32(f32 x);
static f32 tan_f32(f32 x);
static f32 atan_f32(f32 x);
static f32 atan2_f32(f32 x, f32 y);
static f32 ln_f32(f32 x);
static f32 pow_f32(f32 base, f32 x);
static f32 trunc_f32(f32 x);
static f64 sqrt_f64(f64 x);
static f64 sin_f64(f64 x);
static f64 cos_f64(f64 x);
static f64 tan_f64(f64 x);
static f64 atan_f64(f64 x);
static f64 ln_f64(f64 x);
static f64 pow_f64(f64 base, f64 x);
static f32 floor_f32(f32 x);
static f32 ceil_f32(f32 x);

// Vector functions
static v2i32 v2i32_init(i32 x, i32 y);
static v2f32 v2f32_init(f32 x, f32 y);
static v3f32 v3f32_init(f32 x, f32 y, f32 z);
static v4f32 v4f32_init(f32 x, f32 y, f32 z, f32 w);
static v2f32 v2f32_sub(v2f32 a, v2f32 b);
static v2f32 v2f32_add(v2f32 a, v2f32 b);
static v2f32 v2f32_scalar_mult(f32 s, v2f32 a);
static v2f32 v2f32_polar(f32 radius, f32 theta);
static f32 v2f32_mag(v2f32 a);
static f32 v2f32_theta(v2f32 a);

// Range functions
static rangei32 rangei32_init(i32 min, i32 max);

#endif /* end of include guard: BASE_MATH_H */
