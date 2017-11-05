//
//  flint_clock.h
//  Flint
//
//  Created by nuttyshark on 2017/1/13.
//  Copyright 2017 nuttyshark. All rights reserved.
//

#ifndef flint_clock_h
#define flint_clock_h

#include "flint_type.h"
// -_- Notice !! for precsion of integer 32bit, min unit is 10ms

extern flint_i64_t flint_sys_clock;

#define SYS_CLOCK_GO(x) flint_sys_clock+=(x)
#define SYS_CLOCK_RST flint_sys_clock=0

void flint_clock(int src, int *hour, int *min, int *sec);
void flint_clock_inc(int dusec);

#define delay_us(x) {\
    uint32_t _now_nano = flint_sys_clock.lo; \
    while(flint_sys_clock.lo - _now_nano < (x)/10);\
}
#endif /* flint_clock_h */
