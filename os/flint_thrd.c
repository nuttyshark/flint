//
//  flint_thrd.c
//  Flint
//
//  Created by nuttyshark on 2016/12/25.
//  Copyright  2016 nuttyshark. All rights reserved.
//

#include "flint_thrd.h"

static t_flint_thread _thrd_pool[THRD_MAX_NUM];
static uint32_t thrd_mask;

void flint_init_thread(void){
    thrd_mask = 0;
}

t_flint_thread* flint_start_thread(t_flint_task task, void* arg){
	int i;
    t_flint_thread* thrd = 0;
    for(i=0; i<THRD_MAX_NUM; i++){
        if(thrd_mask & (1<<i)){
            continue;
        }else{
            thrd_mask |= (1<<i);
            thrd = _thrd_pool+i;
            thrd->ctx = arg;
            thrd->task = task;
            break;
        }
    }
    thrd->enable = 1;
    thrd->next = 0;
	return thrd;
}

t_flint_task last_task;

void flint_loop_thread(void){
    int i;
    static flint_i64_t lst_clock = {0, 0};
    uint32_t last;
    last = flint_i64_sdist(flint_sys_clock, lst_clock);
    lst_clock = flint_sys_clock;
    //int pass;
    for(i=0; i<THRD_MAX_NUM; i++){
        if(thrd_mask & (1<<i)){
            if(_thrd_pool[i].enable){
                t_flint_thread* thrd = _thrd_pool+i;
                if(thrd->next > last){
                   thrd->next -= last;
                }else{
                    last_task = thrd->task;
                   thrd->next = thrd->task(thrd->ctx);            
                }
            }
        }
    }
    
}

void flint_free_thread(t_flint_thread* thrd){
    // wait for implement
}
