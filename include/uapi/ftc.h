#ifndef __FTC_UAPI_H__
#define __FTC_UAPI_H__

#ifndef CONFIG_TASK_ID
#define CONFIG_TASK_ID 0UL
#endif

#define ___FTC_ENTER_POINT(id, name) \
    void ftc_##id##_enter_point(void) __attribute__((alias(name)))

#define __FTC_ENTER_POINT(id, name) ___FTC_ENTER_POINT(id, name)
#define FTC_ENTER_POINT(name)                 \
    __FTC_ENTER_POINT(CONFIG_TASK_ID, #name); \
    void name(void)

#endif /* __FTC_UAPI_H__ */
