#ifndef __FTC_LIGHTWEIGHT_SYSTEM_H__
#define __FTC_LIGHTWEIGHT_SYSTEM_H__

int __lw_system(char *restrict exec, char *argv[]);

#define compile(exec, argv) ({ __lw_system(exec, argv); })

#endif /* __FTC_LIGHTWEIGHT_SYSTEM_H__ */
