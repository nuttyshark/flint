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


/*
t_flint_alloc* file_pool;

void osfio_init(void){
   FLINT_POOL_INIT(file_pool, sizeof(t_hyio), 10);
}
t_hyio* hyfopen(char* path, HY_IOTYPE type, char mode){
    t_hyio *file = 0;
    switch(type){
        case IO_FF:
        {
#if USE_PLAT == PLAT_STM
            FRESULT result;
            file =  flint_alloc(file_pool);
            file->type = IO_FF;
            result = f_open(&(file->io_ff.file), path, (mode == 'r'?(FA_OPEN_EXISTING|FA_READ):(FA_CREATE_NEW|FA_WRITE)));
            if (result !=  FR_OK)
            {
                flint_free(file_pool, file);
                file = 0;
            }
#else
            return 0;
#endif
        }
            break;
        default:
            break;
    }
    return file;
}

void hyfclose(t_hyio* file){
    switch(file->type){
        case IO_FF:
#if USE_PLAT == PLAT_STM
            f_close(&(file->io_ff.file));
#endif
            break;
        default:
            break;
    }
}

char* hyfgets(char* buf, int max_len ,t_hyio* file){
    switch(file->type){
        case IO_FF:
        {
#if USE_PLAT == PLAT_STM
            buf = f_gets(buf, max_len, &(file->io_ff.file));
            if(buf == 0){
                return 0;
            }
#else
            return 0;
#endif
        }
            break;
        default:
            break;
    }
    return buf;
}

#if USE_PLAT == PLAT_STM


void listRoot(void){
    FRESULT result;
    DIR DirInf;
    FILINFO FileInf;
    uint32_t cnt = 0;
    char fname[256];
    
    result = f_opendir(&DirInf, "2:/nvcnc");    
    if(result != FR_OK){
        return;
    }
    FileInf.lfname = fname;
    FileInf.lfsize = 256;
    for(cnt = 0;;cnt++){
        result = f_readdir(&DirInf, &FileInf);
        if (result != FR_OK || FileInf.fname[0] == 0)
        {
            break;
        }
        if (FileInf.fname[0] == '.')
        {
            continue;
        }
    }
}
#endif

*/