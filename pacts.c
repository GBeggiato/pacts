
#include <assert.h>
#include <stdarg.h>
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

#define PTH_SEP_INT ((int) *PTH_SEP)

#ifndef PTH_DEF
 #define PTH_DEF static inline
#endif

#ifndef PTH_PATH_MAX_SIZE
 #define PTH_PATH_MAX_SIZE PATH_MAX
#endif

// PTH_DEF bool str_contains(char *str, int c) {
//     return strchr(str, c) != NULL;
// }

// PTH_DEF bool str_contains_pth_sep(char *str) {
//     return str_contains(str, PTH_SEP_INT);
// }

PTH_DEF void str_chop_last(char *str, int n) {
    size_t len = strlen(str);
    memset(str+len-n, 0, n);
}

PTH_DEF void pth_checked_vsnprintf(char *str, const char *restrict format, ...) {
    va_list args;
    va_start(args, format);
    int r = vsnprintf(str, PTH_PATH_MAX_SIZE, format, args);
    va_end(args);
    assert((0 <= r && r+1 < PTH_PATH_MAX_SIZE) && "snprintf failed");
}

typedef struct Path {
    char str[PTH_PATH_MAX_SIZE];
} Path;

// create a "Path" from "char *"
Path pth_new(char *name){
    Path path = {0};
    pth_checked_vsnprintf(path.str, "%s", name);
    return path;
}

Path pth_copy(Path *p) {
    Path new = {0};
    memcpy(&new, p, sizeof(Path));
    return new;
}

PTH_DEF void pth_debug(Path *p){
    printf("%s\n", p->str);
}

Path pth_cwd(void) {
    char *cwd = getcwd(NULL, PTH_PATH_MAX_SIZE);
    assert(cwd != NULL && "getcwd failed");
    Path pcwd = pth_new(cwd);
    free(cwd);
    return pcwd;
}

PTH_DEF void pth_resolve(Path *p) {
    char *resolved = realpath(p->str, NULL);
    assert(resolved != NULL && "realpath failed");
    pth_checked_vsnprintf(p->str, "%s", resolved);
    free(resolved);
}

PTH_DEF bool pth_is_absolute(Path *p) {
    char *resolved = realpath(p->str, NULL);
    assert(resolved != NULL && "realpath failed");
    bool ans = strcmp(resolved, p->str) == 0;
    free(resolved);
    return ans;
}

PTH_DEF void pth_parent(Path *p) {
    // delete last char if it's the separator
    size_t n = strlen(p->str);
    char last_char = p->str[n-1];
    if (last_char == PTH_SEP_INT) str_chop_last(p->str, 1);
    // return all the stuff up to the last separator
    char *check = strrchr(p->str, PTH_SEP_INT); // DO NOT FREE THIS PTR
    if (check == NULL) return; 
    size_t m = strlen(check);
    assert(m < n);
    str_chop_last(p->str, m);
}

enum PTH_KIND {
    PTH_KIND_FILE = 1,
    PTH_KIND_DIR,
    PTH_KIND_THERE,
};

PTH_DEF bool pth_is_kind(Path *p, enum PTH_KIND k) {
    struct stat s;
    int is_there = stat(p->str, &s);
    if (is_there != 0) return false;
    switch (k) {
        case PTH_KIND_FILE:  return s.st_mode & S_IFREG;
        case PTH_KIND_DIR:   return s.st_mode & S_IFDIR;
        case PTH_KIND_THERE: return true;
        default:             return false;
    }
}

PTH_DEF bool pth_is_file(Path *p) {
    return pth_is_kind(p, PTH_KIND_FILE);
}

PTH_DEF bool pth_is_dir(Path *p) {
    return pth_is_kind(p, PTH_KIND_DIR);
}

PTH_DEF bool pth_exists(Path *p) {
    return pth_is_kind(p, PTH_KIND_THERE);
}

PTH_DEF void pth_join(Path *p, char *str) {
    size_t len = strlen(p->str);
    pth_checked_vsnprintf(p->str+len, "%s%s", PTH_SEP, str);
}

#undef PTH_PATH_MAX_SIZE
#undef PTH_SEP
#undef PTH_SEP_INT

