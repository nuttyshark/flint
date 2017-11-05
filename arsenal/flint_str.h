//
//  flint_str.h
//  Flint
//
//  Created by nuttyshark on 2016/11/21.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#ifndef flint_str_h
#define flint_str_h

#include "flint_math.h"

#define INVALID_INT 0x7FFFFFFF
#define INVALID_FLOAT  ((float)1e127)

int flint_mvstr(char* src, char* dst);

#define CHAR_NUM(x) ((x)>='0'&&(x)<='9')
#define CHAR_LOWC(x) ((x)>='a'&&(x)<='z')
#define CHAR_UPC(x) ((x)>='A'&&(x)<='Z')

#define TO_NUM(x) ((x)-'0')

int flint_itoa(int src, char* buf);
int flint_atoi(char* buf);
int flint_eqstr(char* src, char* dst);
int flint_strlen(char* src);
void flint_strshift(char* src, int off, char cbit);

float flint_atof(char* buf);
int flint_ftoa(float src, char* buf, int precision);

#endif /* flint_str_h */
