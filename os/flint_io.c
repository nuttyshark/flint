//
//  flint_io.c
//  Flint
//
//  Created by nuttyshark on 2016/12/25.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_io.h"
#include "flint_type.h"
#include "flint_keeper.h"

#define MAX_PIPE_POOL 8

static struct{
    t_flint_pipe* ptrs[MAX_PIPE_POOL];
    int max;
}pipe_pool;

void flint_pipe_init(void){
    pipe_pool.max = 0;
}

void flint_pipe_reg(t_flint_pipe* file){
    pipe_pool.ptrs[pipe_pool.max] = file;
    pipe_pool.max ++;
}

void* flint_pipe_open(char* path, char mode){
    int i;
    for(i=0; i<pipe_pool.max; i++){
        if(flint_eqstr(path, pipe_pool.ptrs[i])){
            break;
        }
    }
    if(i != pipe_pool.max){
        pipe_pool.ptrs[i]->iter = 0;
        pipe_pool.ptrs[i]->tail = 0;
        return pipe_pool.ptrs[i];
    }
    return 0;
}

void flint_pipe_close(void* file){
    
}

char* flint_pipe_gets(char* buf, int max_len, void* file){
    t_flint_pipe* f = file;
    char* walker;
    char* rec = buf;
    if(f->tail == 0){
        buf[0] = 0;
        return buf;
    }
    if(f->iter > 0){
        flint_memcpy(f->ptr+f->iter, f->ptr, f->tail-f->iter);
        f->tail -= f->iter;
        f->iter = 0;
    }
    for(walker = f->ptr, rec = buf; *walker != '\n'; walker ++, rec++){
        *rec = *walker;
    }
    *rec = '\0';
    f->iter += (1 + rec - buf);
    return buf;
}

void flint_pipe_puts(char* buf, void* file){
    t_flint_pipe* f = file;
    int ntail;
    for(; *buf; f->tail ++, buf++){
        f->ptr[f->tail] = *buf;
    }
    f->ptr[f->tail++] = '\n';
}

char f_pipe_eof(void* file){
    return 0;
}

