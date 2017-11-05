//
//  flint_str.c
//  Flint
//
//  Created by nuttyshark on 2016/11/21.
//  Copyright @2016-2025 nuttyshark. All rights reserved.
//

#include "flint_str.h"

#define IS_DIGIT(x) ((x)>='0' && (x)<='9')

int flint_mvstr(char* src, char* dst){
    char *sr = dst;
    for(;*src;src++,dst++){
        *dst = *src;
    }
    *dst = 0;
    return (int)(dst-sr);
}

int flint_eqstr(char* src, char* dst){
    char diff = 0;
    for(;*src;src++,dst++){
        if(*src != *dst){
            return 0;
        }
    }
    if(*src == 0){
        if(*dst != 0){
            return 0;
        }
    }
    return 1;
}

void flint_strshift(char* src, int off, char cbit){
	int slen;
	for(slen = flint_strlen(src) + off; slen >= off; slen --){
		src[slen] = src[slen-off];
	}
	for(;slen>=0;slen--){
		src[slen] = cbit;
	}
}

int flint_strlen(char* src){
	int len;
	for(len=0;*src++;len++);
	return len;
}

int flint_itoa(int src, char* buf){
    int a[10];
    int k = 0;
    int i = 0;
    if(src == 0){
        buf[i++] = '0';
    }else{
        if(src < 0){
            buf[i++] = '-';
            src = -src;
        }
        for(k=0;src;src/=10){
            a[k++] = src % 10;
        }
        while(k--){
            buf[i++] = a[k] + '0';
        }
    }
    buf[i++] = 0;
    return i;
}

int flint_atoi(char* buf){
	int value;
	char flag;
	if(*buf == '-'){
		flag = 1;
		buf++;
	}else{
		flag = 0;
	}
	for(value = 0;*buf;buf++){
		if(!IS_DIGIT(*buf)){
			return INVALID_INT;
		}
		value *= 10;
		value += (*buf-'0');
	}
	return flag?-value:value;
}

float flint_atof(char* buf){
	int dot[2];
	char pt;
	char flag;
	int dbase;
	float value;
	if(*buf == '-'){
		flag = 1;
		buf++;
	}else{
		flag = 0;
	}
	for(dot[0] = 0, dot[1] = 0, pt=0, dbase = 1;*buf;buf++){
		if(IS_DIGIT(*buf)){
			if(pt){
				dbase *= 10;
			}
			dot[pt] *= 10;
			dot[pt] += (*buf-'0');
		}else if(pt == 0 && *buf == '.'){
			pt = 1;
		}else{
			return INVALID_FLOAT;
		}
	}
	value = dot[0]+((float)dot[1])/dbase;
	return flag?-value:value;
}

int flint_ftoa(float src, char* buf, int precision){
    int i=0;
    int mult=1;
    int p = precision==0?4:precision;
    while(p--){
        mult*=10;
    }
    if(src < 0){
        buf[i++] = '-';
        src = -src;
    }
    p = (int)src;
    i += flint_itoa(p, buf+i) - 1;
    p = flint_round(ABS(src - p)*mult);
    if(precision != 0 || p != 0){
        buf[i++] = '.';
        while(mult/=10){
            buf[i++] = '0'+p/mult;
            p%=mult;
            if(p==0 && precision==0){
                break;
            }
        }
    }
    buf[i++] = 0;
    return i;
}

