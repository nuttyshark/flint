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
	FLINT_FRD = 1,
	FLINT_FWR = 2
};

void flint_finit(void);
void* flint_fopen(char* path, char mode);
void flint_fclose(void* file);

char* flint_fgets(char* buf, int max_len, void* file);
char flint_feof(void* file);

typedef int (*flist_callback)(char* fname, int type, int index, void* arg);
int f_list(int lable, int start, int max, char* dir, flist_callback cb, void* arg);

void f_copy(int lable_src, int lable_dst, char* fname);
char* f_path(char* dst, int label, char* fname);

typedef struct{
	char fname[16];
	char* ptr;
	int size;
	int iter;
	int tail;
}t_flint_pipe;

#define OSF_MFILE_INIT(file, name, size) \
{\
	static char __store[size]; \
	static __src_##name; \
	flint_mvstr(file, __src_##name.fname); \
	__src_##name.ptr = __store; \
	__src_##name.size = size; \
	__src_##name.iter = 0; \
	__src_##name.tail = 0; \
	name = &__src_##name; \
	flint_pipe_reg(name); \
}

void flint_pipe_reg(t_flint_pipe*);

void* flint_pipe_open(char* path, char mode);
void flint_pipe_close(void* file);

char* flint_pipe_gets(char* buf, int max_len, void* file);
void flint_pipe_puts(char* buf, void* file);
char f_pipe_eof(void* file);

#endif /* flint_io_h */
