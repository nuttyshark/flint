#include "sys_log.h"

#define MAX_LOG_SEQ 16

struct{
    int lvl;
    f_log log;
}_log_map[MAX_LOG_SEQ];

t_hlog hlog;

void plat_log_init(void);
void plat_log_deinit(void);

void log_init(void){
    int i;
    for(i=0; i<MAX_LOG_SEQ; i++){
        _log_map[i].lvl = -1;
    }
    plat_log_init();

}

void log_deinit(void){
    plat_log_deinit();
}

void reg_lvl(int lvl, f_log log_func){
    int i;
    for(i=0; i<MAX_LOG_SEQ; i++){
        if(-1 == _log_map[i].lvl || lvl == _log_map[i].lvl){
            _log_map[i].log = log_func;
            break;
        }
    }
    switch(lvl){
    case LOG_TRACE:
        hlog.trace = log_func;
        break;
    case LOG_INFO:
        hlog.info = log_func;
        break;
    case LOG_DEBUG:
        hlog.debug = log_func;
        break;
    case LOG_WARN:
        hlog.warn = log_func;
        break;
    case LOG_ERR:
        hlog.err = log_func;
        break;
    default:
        break;
    }
}
