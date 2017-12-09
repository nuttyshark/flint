#ifndef _SYS_LOG_H_
#define _SYS_LOG_H_

typedef void(*f_flint_log)(const char* format, ...);

enum{
    LOG_TRACE = 0,
    LOG_INFO = 1,
    LOG_DEBUG = 2,
    LOG_WARN = 3,
    LOG_ERR = 4,
    LOG_CUSTOM = 5
};

void flint_log_init(void);
void flint_log_deinit(void);
void flint_log_reg(int lvl, f_flint_log);

typedef struct{
    f_flint_log trace;
    f_flint_log info;
    f_flint_log debug;
    f_flint_log warn;
    f_flint_log err;
}t_flint_hlog;

extern t_flint_hlog flint_hlog;

#endif
