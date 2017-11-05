#ifndef _SYS_LOG_H_
#define _SYS_LOG_H_

typedef void(*f_log)(const char* format, ...);

enum{
    LOG_TRACE = 0,
    LOG_INFO = 1,
    LOG_DEBUG = 2,
    LOG_WARN = 3,
    LOG_ERR = 4,
    LOG_CUSTOM = 5
};

void log_init(void);
void log_deinit(void);
void reg_lvl(int lvl, f_log);

typedef struct{
    f_log trace;
    f_log info;
    f_log debug;
    f_log warn;
    f_log err;
}t_hlog;

extern t_hlog hlog;

#endif
