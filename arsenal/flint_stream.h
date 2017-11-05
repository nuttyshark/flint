//
//  flint_stream.h
//  Flint
//
//  Created by nuttyshark on 2016/12/8.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_stream_h
#define flint_stream_h

#include <stdio.h>
#include "flint_type.h"
#include "flint_keeper.h"

//行编辑标记机制

typedef struct{
    FILE* fp;
    int line;
    char st_buf[32];
    uint32_t line_off[32];
    uint32_t sub_off[64];
}t_flint_file;

void flint_stream_init(void);

t_flint_file* flint_open_file(char* filename);

int flint_read_line(t_flint_file* file, int line);
int flint_read_line_to(t_flint_file* file, int line, char* buf);

void flint_close_file(t_flint_file* file);

#endif /* flint_stream_h */
