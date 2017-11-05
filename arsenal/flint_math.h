//
//  flint_math.h
//  Flint
//
//  Created by nuttyshark on 2016/11/27.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_math_h
#define flint_math_h

#include "flint_type.h"

#define EQUAL_LIMIT ((float)0.00001)
#define FLOAT_EQUAL(x, y)  (ABS((x)-(y))<EQUAL_LIMIT)
#define ABS(x) ((x)>0?(x):(-(x)))

#define PI 3.1415926535f

int flint_round(float t);

float flint_quake_sqrt(float x);

float flint_dist(float x1, float y1, float x2, float y2);

void flint_vector_unit(float* src, float* dst, int axis, float* s_dist);

#endif /* flint_math_h */
