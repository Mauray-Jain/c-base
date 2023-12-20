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
