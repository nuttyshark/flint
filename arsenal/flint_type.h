//
//  flint_type.h
//  Flint
//
//  Created by nuttyshark on 2016/11/26.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_type_h
#define flint_type_h

typedef unsigned char uint8_t;
typedef unsigned short uint16_t;
typedef unsigned int uint32_t;
typedef short int16_t;
typedef int int32_t;

typedef union{
	struct{
		int min;
		int max;
	}_i;
	struct{
		float min;
		float max;
	}_f;
	struct{
		int mlen;
	}_s;
}t_rvalid;

typedef struct{
    uint32_t lo;
    int32_t hi;
}flint_i64_t;

#define flint_i64_sdist(x, y) (x).lo - (y).lo
#define flint_i64_rever(x) (x).hi = -(x).hi-((x).lo>0),(x).lo = 0-(x).lo
#define flint_i64_set(x, y) (x).hi = ((y)>=0?0:-1),(x).lo = (y)
#define flint_i64_copy(x, y) (x).hi = (y).hi,(x).lo = (y).lo
#define flint_i64_put(x, y, z) (x).lo = (y);(x).hi = (z)
#define flint_i64_equal(x, y) ((x).lo == (y).lo && (x).hi == (y).hi)

void flint_i64_inc(flint_i64_t*, uint32_t);
void flint_i64_dec(flint_i64_t*, uint32_t);
void flint_i64_add(flint_i64_t* op1, flint_i64_t* op2, flint_i64_t* res);
void flint_i64_umul(flint_i64_t* s1, uint32_t s2, flint_i64_t* res);
void flint_i64_udiv(flint_i64_t*, uint32_t, flint_i64_t* res);

#define nil (-1)


#endif /* flint_type_h */
