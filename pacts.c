
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
#endif

#ifndef PTH_PATH_MAX_SIZE
 #define PTH_PATH_MAX_SIZE PATH_MAX
#endif

PTH_DEF bool str_contains(char *str, int c) {
    return strchr(str, c) != NULL;
}

PTH_DEF bool str_contains_pth_sep(char *str) {
    return str_contains(str, (int) *PTH_SEP);
}

typedef struct Path {
    char str[PTH_PATH_MAX_SIZE];
} Path;


/*
 * create a "Path" from "char *"
 *
 * stores the resolved path in "str"
 *
 * fails in case of errors
 */
Path pth_new(char *name){
    char *resolved = realpath(name, NULL);
    assert(resolved != NULL && "realpath failed");
    Path path = {0};
    int r = snprintf(path.str, PTH_PATH_MAX_SIZE, "%s", resolved);
    assert((r >= 0 && r+1 < PTH_PATH_MAX_SIZE) && "snprintf failed");
    free(resolved);
    return path;
}

Path pth_copy(Path *p) {
    return pth_new(p->str);
}

Path pth_parent(Path *child) {
    Path parent = pth_new(child->str);
    size_t n = strlen(parent.str);
    char *check = strrchr(parent.str, (int) *PTH_SEP);
    if (check == NULL) return parent;
    size_t m = strlen(check);
    assert(m < n);
    size_t last_char = n - m;
    memset(parent.str+last_char, 0, m);
    return parent;
}


Path pth_cwd(void) {
    char *cwd = getcwd(NULL, PTH_PATH_MAX_SIZE);
    assert(cwd != NULL && "getcwd failed");
    return pth_new(cwd);
}


enum _pth_kind {
    PTH_KIND_FILE = 1,
    PTH_KIND_DIR,
    PTH_KIND_THERE,
};

bool _pth_is_kind(Path *p, enum _pth_kind k) {
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

bool pth_is_file(Path *p) {
    return _pth_is_kind(p, PTH_KIND_FILE);
}

bool pth_is_dir(Path *p) {
    return _pth_is_kind(p, PTH_KIND_DIR);
}

bool pth_exists(Path *p) {
    return _pth_is_kind(p, PTH_KIND_THERE);
}

void pth_debug(Path *p){
    printf("%s\n", p->str);
}

#undef PTH_PATH_MAX_SIZE
#undef PTH_SEP

