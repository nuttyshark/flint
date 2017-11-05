//
//  flint_type.c
//  Flint
//
//  Created by nuttyshark on 2016/11/26.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_type.h"

#define LOW_MAX 0xFFFFFFFFUL

void flint_i64_inc(flint_i64_t* src, uint32_t num){
    num += src->lo;
    if(num < src->lo){
        src->hi ++;
    }
    src->lo = num;
}

void flint_i64_dec(flint_i64_t* src, uint32_t num){
    if(src->lo < num){
        src->hi --;
    }
    src->lo -= num;
}

void flint_i64_add(flint_i64_t* op1, flint_i64_t* op2, flint_i64_t* res){
    res->hi = op1->hi + op2->hi;
    res->lo = op1->lo + op2->lo;
    if(op2->lo > LOW_MAX - op1->lo){
        res->hi ++;
    }
}

void flint_i64_umul(flint_i64_t* s1, uint32_t s2, flint_i64_t* res){
	unsigned int s1_d[4];
	unsigned int s2_d[2];
	unsigned int res_sd[7] = {0};
	int i, j;
	s1_d[0] = s1->lo & 0xFFFF;
	s1_d[1] = s1->lo >> 16;
	s1_d[2] = s1->hi & 0xFFFF;
	s1_d[3] = s1->hi >> 16;
	s2_d[0] = s2 & 0xFFFF;
	s2_d[1] = s2 >> 16;
	for(i=0; i<4; i++){
		for(j=0; j<2; j++){
			res_sd[i+j] += s1_d[i]*s2_d[j]; 
		}
	}
	for(i=0; i<6; i++){
		res_sd[i+1] += (res_sd[i]>>16);
		res_sd[i] &= 0xFFFF;
	}
	res->lo = res_sd[0]|(res_sd[1]<<16);
	res->hi = res_sd[2]|(res_sd[3]<<16);
}

void flint_i64_udiv(flint_i64_t* src, uint32_t div, flint_i64_t* res){
    uint32_t tmpr;
    uint32_t bit;
    res->hi = src->hi / div;
    res->lo = 0;
    tmpr = src->hi % div;
    for(bit=(1UL<<31); bit>0; bit>>=1){
        tmpr = (tmpr<<1) + ((src->lo&bit)?1:0);
        // because this tmpr is mult by 2 one time , so direct minus is available
        // x < y -> x*2 < y*2 -> (x<<1)/y < 2
        if(tmpr > div){
            res->lo |= bit;
            tmpr -= div;
        }
    }
}
