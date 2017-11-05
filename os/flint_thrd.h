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

typedef int(*t_hytask)(void* arg);

typedef struct{
    char enable;
    t_hytask task;
    void* ctx;
    unsigned int next;
}t_hythread;

void init_hyThread(void);

t_hythread* start_hyThread(t_hytask task, void* arg);

void loop_hyThread(void);

void free_hyThread(t_hythread*);

#endif /* flint_thrd_h */
