#ifndef __VERSION_H__
#define __VERSION_H__

#define ___current_version(_v, _p, _s) "v" #_v "." #_p "." #_s
#define __current_version(_v, _p, _s) ___current_version(_v, _p, _s)

#define current_version() \
    __current_version(CONFIG_VERSION, CONFIG_PATCHLEVEL, CONFIG_SUBLEVEL)

#endif /* __VERSION_H__ */
