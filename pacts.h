
#ifndef PTH_H_
#define PTH_H_

#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* NOT ACCOUNTED FOR YET */
#ifdef _WIN32
 #define WIN32_LEAN_AND_MEAN
 #define _WINUSER_
 #define _WINGDI_
 #define _IMM_
 #define _WINCON_
 #include <windows.h>
 #include <direct.h>
 #include <shellapi.h>
 #define PTH_SEP "\\"
#else
 #include <linux/limits.h>
 #include <sys/types.h>
 #include <sys/wait.h>
 #include <sys/stat.h>
 #include <unistd.h>
 #include <fcntl.h>
 #define PTH_SEP "/"
#endif

#ifndef PTH_DEF
 #define PTH_DEF static inline
#endif // PTH_DEF

#ifndef PTH_PATH_MAX
 #define PTH_PATH_MAX PATH_MAX
#endif // PTH_PATH_MAX


PTH_DEF bool str_contains(char *str, int c);
PTH_DEF bool str_contains_pth_sep(char *str);


#endif // PTH_H_

# =============================================================================

#ifdef PTH_IMPLEMENTATION

PTH_DEF bool str_contains(char *str, int c) {
    return strchr(str, c) != NULL;
}

PTH_DEF bool str_contains_pth_sep(char *str) {
    return str_contains(str, (int) *PTH_SEP);
}

hg  #endif // PTH_IMPLEMENTATION
