//
//  flint_keeper.h
//  Flint
//
//  Created by nuttyshark on 2016/11/19.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_keeper_h
#define flint_keeper_h

#include "flint_type.h"

typedef struct{
    uint16_t msize;
    uint16_t head;
    uint16_t tail;
    uint16_t lst_tail;
    void ** ptr;
}t_flint_queue;

int flint_fifo_len(t_flint_queue *queue);
void* flint_fifo_pop(t_flint_queue *queue);
int flint_fifo_push(t_flint_queue *queue, void* src);
int flint_fifo_left(t_flint_queue *queue);

#define FLINT_FIFO_INIT(type, name, size) \
{\
    static type *__store[size];\
    static t_flint_queue __src_##name;\
    __src_##name.ptr = (void**)__store;\
    __src_##name.msize = (size);\
    __src_##name.head = 0;\
    __src_##name.tail = 0;\
    __src_##name.lst_tail = (size)-1;\
    name = &__src_##name;\
}

typedef struct{
    uint32_t unit;
    uint16_t bsize;
    uint16_t used;
    void* pool;
    uint32_t* mask;
    uint32_t* mask_xor;
}t_flint_alloc;

// __align(4)

#define FLINT_POOL_INIT(name,unit,size) \
    {\
        static t_flint_alloc alloc; \
        static uint32_t __src_mask_##name[(1+((size-1)>>5))<<1];\
        static uint8_t __flint_alloc_pool_##name[size*unit];\
        name = &alloc; \
        _keeper_mgr_push(name); \
        _flint_init_alloc(name, \
                    __flint_alloc_pool_##name, \
                    __src_mask_##name, \
                    size, \
                    unit); \
    }

#define KEEPER_NUM 32

extern t_flint_alloc* keeper_mgr[KEEPER_NUM];

void _keeper_mgr_push(t_flint_alloc*);

int _flint_init_alloc(t_flint_alloc* alloc, uint8_t* mem, uint32_t* mask, int size, int unit_size);
void *flint_alloc(t_flint_alloc* pool);
void *flint_allocz(t_flint_alloc* pool);
int flint_free(t_flint_alloc* pool, void *ptr);
int flint_gfree(void *ptr);
void flint_memclr(void* mem, uint8_t v, int len);
void flint_memcpy(const void* from, void* to, int len);
char flint_memcmp(const void* from, const void* to, int len);
void* flint_fifo_preget(t_flint_queue *queue, int pcnt);
int flint_fifo_preset(t_flint_queue *queue, void* sr, int pcnt);

#endif /* flint_keeper_h */
