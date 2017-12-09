#include "flint_log.h"

#define MAX_LOG_SEQ 16

struct{
    int lvl;
    f_flint_log log;
}_log_map[MAX_LOG_SEQ];

t_flint_hlog flint_hlog;

void plat_log_init(void);
void plat_log_deinit(void);

void flint_log_init(void){
    int i;
    for(i=0; i<MAX_LOG_SEQ; i++){
        _log_map[i].lvl = -1;
    }
    plat_log_init();

}

void flint_log_deinit(void){
    plat_log_deinit();
}

void flint_log_reg(int lvl, f_flint_log log_func){
    int i;
    for(i=0; i<MAX_LOG_SEQ; i++){
        if(-1 == _log_map[i].lvl || lvl == _log_map[i].lvl){
            _log_map[i].log = log_func;
            break;
        }
    }
    switch(lvl){
    case LOG_TRACE:
        flint_hlog.trace = log_func;
        break;
    case LOG_INFO:
        flint_hlog.info = log_func;
        break;
    case LOG_DEBUG:
        flint_hlog.debug = log_func;
        break;
    case LOG_WARN:
        flint_hlog.warn = log_func;
        break;
    case LOG_ERR:
        flint_hlog.err = log_func;
        break;
    default:
        break;
    }
}
