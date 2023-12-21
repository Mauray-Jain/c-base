#include "math.h"

static f32 inf_f32(void){
	u32 inf = 0x7f800000;
	f32 *p = (f32*) &inf;
	return (*p);
}

static f32 neg_inf_f32(void){
	u32 inf = 0xff800000;
	f32 *p = (f32*) &inf;
	return (*p);
}

static f64 inf_f64(void){
	u64 inf = 0x7ff0000000000000;
	f64 *p = (f64*) &inf;
	return (*p);
}

static f64 neg_inf_f64(void){
	u64 inf = 0xff80000000000000;
	f64 *p = (f64*) &inf;
	return (*p);
}

// Float functions

static f32 abs_f32(f32 x) {
	u32* p = (u32*) &x;
	*p &= 0x7fffffff;
	return *((f32*)p);
}

static f64 abs_f64(f64 x) {
	u64* p = (u64*) &x;
	*p &= 0x7fffffffffffffff;
	return *((f64*)p);
}

static f32 sign_f32(f32 x){
	u32* p = (u32*) &x;
  f32 result = ((*p) & 0x80000000)?-1.f:1.f;
  return result;
}

static f64 sign_f64(f64 x){
	u64* p = (u64*) &x;
  f64 result = ((*p) & 0x8000000000000000)?-1.:1.;
  return result;
}

#include <math.h>

static f32 sqrt_f32(f32 x){
  return(sqrtf(x));
}

static f32 sin_f32(f32 x){
  return(sinf(x));
}

static f32 cos_f32(f32 x){
  return(cosf(x));
}

static f32 tan_f32(f32 x){
  return(tanf(x));
}

static f32 atan_f32(f32 x){
  return(atanf(x));
}

static f32 atan2_f32(f32 x, f32 y){
  return(atan2f(y, x));
}

static f32 ln_f32(f32 x){
  return(logf(x));
}

static f32 pow_f32(f32 base, f32 x){
  return(powf(base, x));
}

static f64 sqrt_f64(f64 x){
  return(sqrt(x));
}

static f64 sin_f64(f64 x){
  return(sin(x));
}

static f64 cos_f64(f64 x){
  return(cos(x));
}

static f64 tan_f64(f64 x){
  return(tan(x));
}

static f64 atan_f64(f64 x){
  return(atanf(x));
}

static f64 ln_f64(f64 x){
  return(log(x));
}

static f64 pow_f64(f64 base, f64 x){
  return(powf(base, x));
}

static f32 trunc_f32(f32 x){
  return((f32)(i32)x);
}

static f32 floor_f32(f32 x){
  f32 r = (f32)((i32)x);
  if (r > x){
    r -= 1.f;
  }
  return(r);
}

static f32 ceil_f32(f32 x){
  f32 r = (f32)((i32)x);
  if (r < x){
    r += 1.f;
  }
  return(r);
}

// Vector Functions

static v2i32 v2i32_init(i32 x, i32 y){
  v2i32 r = {x, y};
  return r;
}

static v2f32 v2f32_init(f32 x, f32 y){
  v2f32 r = {x, y};
  return r;
}

static v3f32 v3f32_init(f32 x, f32 y, f32 z){
  v3f32 r = {x, y, z};
  return r;
}

static v4f32 v4f32_init(f32 x, f32 y, f32 z, f32 w){
  v4f32 r = {x, y, z, w};
  return r;
}

static v2f32 v2f32_sub(v2f32 a, v2f32 b){
	v2f32 r = {a.x - b.x, a.y - b.y};
	return r;
}

static v2f32 v2f32_add(v2f32 a, v2f32 b){
	v2f32 r = {a.x + b.x, a.y + b.y};
	return r;
}

static v2f32 v2f32_scalar_mult(f32 s, v2f32 a){
	v2f32 r = {a.x * s, a.y * s};
	return r;
}

static v2f32 v2f32_polar(f32 radius, f32 theta){
	v2f32 r = {radius * cos_f32(theta), radius * sin_f32(theta)};
	return r;
}

static f32 v2f32_mag(v2f32 a){
	f32 sum = pow_f32(a.x, 2) + pow_f32(a.y, 2);
	return sqrt_f32(sum);
}

static f32 v2f32_theta(v2f32 a){
	return atan_f32(a.y / a.x);
}

// Range functions

static rangei32 rangei32_init(i32 min, i32 max){
	rangei32 r;
	if (min < max) {
		r.min = min;
		r.max = max;
	} else {
		r.min = max;
		r.max = min;
	}
	return r;
}
