//
//  flint_math.c
//  Flint
//
//  Created by nuttyshark on 2016/11/27.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_math.h"

float flint_quake_sqrt(float x)
{
    float xhalf = 0.5f*x;
    int i = *(int*)&x;
    i = 0x5f375a86- (i>>1);
    x = *(float*)&i;
    x = x*(1.5f-xhalf*x*x);
    return 1/x;
}

int flint_round(float t){
    if(FLOAT_EQUAL(t, 0)){
        return 0;
    }
    if(t>0){
        return (int)(t+(float)0.5);
    }else{
        return (int)(t-(float)0.5);
    }
}

void flint_vector_unit(float* src, float* dst, int axis_mask, float* s_dist){
    int i;
    float dist;
    dist = 0;
    for(i=0; i<6; i++){
        if(axis_mask & (1<<i)){
            dist += src[i]*src[i];
        }
    }
    dist = flint_quake_sqrt(dist);
    *s_dist = dist;
    for(i=0; i<6; i++){
        if(axis_mask & (1<<i)){
            dst[i] = src[i]/dist;
        }
    }
}

float flint_dist(float x1, float y1, float x2, float y2){
    return flint_quake_sqrt((x1-x2)*(x1-x2) + (y1 - y2)*(y1-y2));
}
