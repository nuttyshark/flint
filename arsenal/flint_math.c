//
//  flint_math.c
//  Flint
//
//  Created by nuttyshark on 2016/11/27.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_math.h"
#include "math.h"

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

float flint_circle_len(float x1, float y1, float x2, float y2, float r, char dir){
    float len;
    float dx, dy;
    float zeta;
    dx = x2-x1;
    dy = y2-y1;
    len = (flint_quake_sqrt(dx*dx + dy*dy))/2;
    zeta = (float)(2*asin(len/r));
    if(dir){
        zeta = 2*PI-zeta;
    }
    return zeta * r;
}

char flint_circle_cent(float x1,float y1,float x2,float y2,float r,float *xd,float *yd)
{
    float dx;
    float dy;
    float R;
    int r_dir;
    float x[2];
    float y[2];
    dx = (float)0.5*(y1-y2);
    dy = (float)0.5*(x2-x1);
    R  = dx*dx+dy*dy;
    r_dir = r>0?1: 0;
    r = r>0?r: -r;
    if( R<(float)0.0001 || r*r<R )
        return 0;
    r = flint_quake_sqrt(r*r-R)/flint_quake_sqrt(R);
    dx *= r;
    dy *= r;
    x[0] = (float)0.5*(x1+x2)+dx;
    y[0] = (float)0.5*(y1+y2)+dy;
    x[1] = (float)0.5*(x1+x2)-dx;
    y[1] = (float)0.5*(y1+y2)-dy;
    if(( r_dir &&  (x1-x2)*(y[0]-y2) - (y1-y2)*(x[0]-x2) > 0 ) ||
       (!r_dir &&  (x1-x2)*(y[0]-y2) - (y1-y2)*(x[0]-x2) < 0 )) {
        *xd = x[0];
        *yd = y[0];
    }else{
        *xd = x[1];
        *yd = y[1];
    }
    return 1;
}

static struct{
    float l;
    float r;
    float ai;
    float bi;
}_flint_circle_cal = {0,0,0,0};

void _flint_update_circle_cal(float l, float r){
    if(!(FLOAT_EQUAL(l, _flint_circle_cal.l) && FLOAT_EQUAL(r, _flint_circle_cal.r))){
        //update circle cal unit
        float dzta;
        float udt;
        _flint_circle_cal.l = l;
        _flint_circle_cal.r = r;
        dzta = l/r;
        udt = (dzta*dzta)/(float)4.0;
        _flint_circle_cal.ai = (1-udt)/(1+udt);
        _flint_circle_cal.bi = dzta/(1+udt);
    }
}

void flint_next_p_on_circle(float xi, float yi, float l, float r, float *dx, float *dy, char dir){
    _flint_update_circle_cal(l, r);
    if(dir){
        *dx = _flint_circle_cal.ai*xi - _flint_circle_cal.bi*yi - xi;
        *dy = _flint_circle_cal.ai*yi + _flint_circle_cal.bi*xi - yi;
    }else{
        xi = -xi;
        *dx = _flint_circle_cal.bi*yi - _flint_circle_cal.ai*xi + xi;
        *dy = _flint_circle_cal.ai*yi + _flint_circle_cal.bi*xi - yi;
    }
}

float flint_dist(float x1, float y1, float x2, float y2){
    return flint_quake_sqrt((x1-x2)*(x1-x2) + (y1 - y2)*(y1-y2));
}
