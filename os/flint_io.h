//
//  flint_io.h
//  Flint
//
//  Created by nuttyshark on 2016/12/25.
//  Copyright  2016  nuttyshark. All rights reserved.
//

#ifndef flint_io_h
#define flint_io_h

#include "flint_os.h"

enum{
	HY_FRD = 1,
	HY_FWR = 2
};

void f_init(void);
void* f_open(char* path, char mode);
void f_close(void* file);

char* f_gets(char* buf, int max_len, void* file);
char f_eof(void* file);

#endif /* flint_io_h */
