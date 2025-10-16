/*
 * the general idea is Pathlib from python3
 *
 * goals are: 
 * - intuitive api
 * - no memory management and no stateful library
 * - stdio.h ease of interaction
 *
 */

// TODO:
// 1. determine with OS we are running on
// 2. implement concat of parts (os.join)
// 3. get name
// 4. get stem
// 5. get suffix
// 6. get parent
// 7. change name/stem/prefix
// 8. is_file, is_dir
// 9. iterdir and following recipies
// MAN Pages: unlink, open, ...

#include <assert.h>
#include <linux/limits.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

#ifndef PTH_PATH_MAX
 #define PTH_PATH_MAX PATH_MAX
#endif

// not accounted for now
#ifdef _WIN32
 #define PTH_SEP "\\"
#else
 #define PTH_SEP "/"
#endif

typedef struct {
    char str[PTH_PATH_MAX];
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
    int r = snprintf(path.str, PTH_PATH_MAX, "%s", resolved);
    assert((r >= 0 && r+1 < PTH_PATH_MAX) && "snprintf failed");
    free(resolved);
    return path;
}

Path pth_cwd(void) {
    char *cwd = getcwd(NULL, PTH_PATH_MAX);
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

#undef PTH_PATH_MAX
#undef PTH_SEP


// =============================================================================

int main(void) {
    Path cwd = pth_cwd();
    pth_debug(&cwd);

    if (pth_exists(&cwd)) printf("cwd exists = true");
    else printf("cwd exists = false");
    printf("\n");

    if (pth_is_dir(&cwd)) printf("cwd is dir = true");
    else printf("cwd is dir = false");
    printf("\n");

    if (pth_is_file(&cwd)) printf("cwd is file = true");
    else printf("cwd is file = false");
    printf("\n");

    return 0;
}

