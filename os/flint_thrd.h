//
//  flint_thrd.h
//  Flint
//
//  Created by nuttyshark on 2016/12/25.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_thrd_h
#define flint_thrd_h

#include "flint_os.h"
#include "flint_type.h"
#include "flint_clock.h"

#define THRD_MAX_NUM 20

typedef int(*t_flint_task)(void* arg);

typedef struct{
    char enable;
    t_flint_task task;
    void* ctx;
    unsigned int next;
}t_flint_thread;

void flint_init_thread(void);

t_flint_thread* flint_start_thread(t_flint_task task, void* arg);

void flint_loop_thread(void);

void flint_free_thread(t_flint_thread*);

#endif /* flint_thrd_h */
