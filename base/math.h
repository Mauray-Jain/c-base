#ifndef BASE_MATH_H
#define BASE_MATH_H

#include "types.h"

f32 inf_f32(void);
f32 neg_inf_f32(void);

f64 inf_f64(void);
f64 neg_inf_f64(void);

// Math functions on float
f32 sign_f32(f32 x);
f64 sign_f64(f64 x);
f32 abs_f32(f32 x);
f64 abs_f64(f64 x);
f32 sqrt_f32(f32 x);
f32 sin_f32(f32 x);
f32 cos_f32(f32 x);
f32 tan_f32(f32 x);
f32 atan_f32(f32 x);
f32 atan2_f32(f32 x, f32 y);
f32 ln_f32(f32 x);
f32 pow_f32(f32 base, f32 x);
f32 trunc_f32(f32 x);
f64 sqrt_f64(f64 x);
f64 sin_f64(f64 x);
f64 cos_f64(f64 x);
f64 tan_f64(f64 x);
f64 atan_f64(f64 x);
f64 ln_f64(f64 x);
f64 pow_f64(f64 base, f64 x);
f32 floor_f32(f32 x);
f32 ceil_f32(f32 x);

// Vector functions
v2i32 v2i32_init(i32 x, i32 y);
v2f32 v2f32_init(f32 x, f32 y);
v3f32 v3f32_init(f32 x, f32 y, f32 z);
v4f32 v4f32_init(f32 x, f32 y, f32 z, f32 w);
v2f32 v2f32_sub(v2f32 a, v2f32 b);
v2f32 v2f32_add(v2f32 a, v2f32 b);
v2f32 v2f32_scalar_mult(f32 s, v2f32 a);
v2f32 v2f32_polar(f32 radius, f32 theta);
f32 v2f32_mag(v2f32 a);
f32 v2f32_theta(v2f32 a);

// Range functions
rangei32 rangei32_init(i32 min, i32 max);

#endif /* end of include guard: BASE_MATH_H */
