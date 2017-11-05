//
//  flint_clock.c
//  Flint
//
//  Created by nuttyshark on 2017/1/13.
//  Copyright 2017  nuttyshark. All rights reserved.
//

#include "flint_clock.h"

flint_i64_t flint_sys_clock;

void flint_clock_inc(int dusec){
    flint_i64_inc(&flint_sys_clock, dusec);
}

void flint_clock_init(void){
    flint_i64_set(flint_sys_clock, 0);
}

void flint_clock(int src, int *hour, int *min, int *sec){
    *sec = (src/100) %60;
    *min = (src /6000)%60;
    *hour = src /360000;
}
