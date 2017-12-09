//
//  flint_keeper.c
//  Flint
//
//  Created by nuttyshark on 2016/11/19.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_keeper.h"

t_flint_alloc* keeper_mgr[KEEPER_NUM]={0};

void _keeper_mgr_push(t_flint_alloc* alloc){
    int i;
    for(i=0; i<KEEPER_NUM; i++){
        if(keeper_mgr[i]){
            continue;
        }else{
            keeper_mgr[i] = alloc;
            break;
        }
    }
}

int flint_gfree(void* ptr){
    int i;
    for(i=0; i<KEEPER_NUM; i++){
        t_flint_alloc* alloc = keeper_mgr[i];
        if(alloc != 0){
            if(alloc->pool <= ptr &&
               (uint8_t*)alloc->pool+alloc->bsize*alloc->unit > (uint8_t*)ptr){
                return flint_free(alloc, ptr);
            }
        }else{
            break;
        }
    }
    return 0;
}


void* flint_fifo_pop(t_flint_queue *queue){
    if(queue->head != queue->tail){
        void* rt;
        rt = queue->ptr[queue->tail];
        queue->lst_tail = queue->tail;
        queue->tail ++;
        if(queue->tail >= queue->msize){
            queue->tail = 0;
        }
        return rt;
    }
    return 0;
}

int flint_fifo_push(t_flint_queue *queue, void* sr){
    if(queue->head != queue->lst_tail){
        queue->ptr[queue->head] = sr;
        queue->head ++;
        if(queue->head >= queue->msize){
            queue->head = 0;
        }
        return 0;
    }
    return 1;
}

void* flint_fifo_preget(t_flint_queue *queue, int pcnt){
    if(pcnt > flint_fifo_len(queue)){
        return 0;
    }else{
        int req_pos = queue->head - pcnt;
        req_pos = req_pos >= 0?req_pos:req_pos+queue->msize;
        return queue->ptr[req_pos];
    }
}

int flint_fifo_preset(t_flint_queue *queue, void* sr, int pcnt){
    if(pcnt > flint_fifo_len(queue)){
        return 1;
    }else{
        int req_pos = queue->head - pcnt;
        req_pos = req_pos >= 0?req_pos:req_pos+queue->msize;
        queue->ptr[req_pos] = sr;
        return 0;
    }
}

int flint_fifo_len(t_flint_queue *queue){
    int len = queue->head - queue->tail;
    return len >= 0?len:len+queue->msize;
}

int flint_fifo_left(t_flint_queue *queue){
	return queue->msize - flint_fifo_len(queue);
}

int _flint_init_alloc(t_flint_alloc* alloc, uint8_t* mem, uint32_t* mask, int size, int unit_size){
    int i;
    alloc->unit = unit_size;
    alloc->pool = mem;
    alloc->mask = mask;
    alloc->mask_xor = mask+(1+((size-1)>>5));
    alloc->bsize = size;
    alloc->used = 0;
    for(i=0; i<size; i+=32){
        alloc->mask[i>>5] = 0xFFFFFFFF;
        alloc->mask_xor[i>>5] = 0;
    }
    return 0;
}

void *flint_alloc(t_flint_alloc* pool){
    int fnd;
    int fmax = (pool->bsize-1)>>5;
    for(fnd = 0; fnd <= fmax; fnd++){
        uint32_t pool_available;
        pool_available = pool->mask[fnd] ^ pool->mask_xor[fnd];
        if(pool_available){
            // has pos
            int smax = pool->bsize - (fnd<<5);
            int spos;
            smax = smax >= 32?32:smax;
            for(spos = 0; spos < smax; spos ++){
                uint32_t r_mask;
                r_mask = 1U<<spos;
                if(r_mask & pool_available){
                    pool->used ++;
                    pool->mask[fnd] ^= r_mask;
                    return (uint8_t*)pool->pool+(((fnd<<5)+spos)*pool->unit);
                }
            }
        }
    }
    return 0;
}

void *flint_allocz(t_flint_alloc* pool){
    uint8_t *ret;
    ret = flint_alloc(pool);
    if(ret){
        flint_memclr(ret, 0, pool->unit);
    }
    return ret;
}
int flint_free(t_flint_alloc* pool, void *ptr){
    int pos;
    int fnd;
    pos = (int)((uint8_t*)ptr - (uint8_t*)pool->pool);
    if(pos % pool->unit){
        return 1;
    }
    pos /= pool->unit;
    fnd = pos>>5;
    pos = pos&0x1F;
    if(0 == ((pool->mask[fnd]^pool->mask_xor[fnd]) & (1U<<pos))){
        pool->mask_xor[fnd] ^= (1U<<pos);
    }else{
        pos ++;
    }
    pool->used --;
    return 0;
}


void flint_memclr(void* mem, uint8_t v, int len){
    if(len > 16){
        uint32_t dst;
        int i;
        ((uint8_t*)&dst)[0] = v;
        ((uint8_t*)&dst)[1] = v;
        ((uint8_t*)&dst)[2] = v;
        ((uint8_t*)&dst)[3] = v;
        for(i=0; i<len>>2; i++){
            ((uint32_t*)mem)[i] = dst;
        }
        len &= 0x3;
        mem = (uint8_t*)mem + (i<<2);
    }
    for(len = len-1; len >= 0; len--){
        ((uint8_t*)mem)[len] = v;
    }
}

void flint_memcpy(const void* from, void* to, int len){
    for(;len > 3 ;len -= 4){
        *((uint32_t*)to) = *((uint32_t*)from);
        to = (uint8_t*)to + 4;
        from = (uint8_t*)from + 4;
    }
    while(len--){
        *((uint8_t*)to) = *((uint8_t*)from);
        to = (uint8_t*)to + 1;
        from = (uint8_t*)from + 1;
    }
}

char flint_memcmp(const void* from, const void* to, int len){
    for(;len > 3 ;len -= 4){
		if(*((uint32_t*)to) != *((uint32_t*)from)){
			return 1;
		}
    }
    while(len--){
		if(*((uint8_t*)to) != *((uint8_t*)from)){
			return 1;
		}
    }
	return 0;
}
