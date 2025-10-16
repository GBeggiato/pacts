/*
 * the general idea is Pathlib from python3
 *
 * goals are: 
 * - intuitive api
 * - no memory management
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
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#ifndef PTH_PATH_MAX
#define PTH_PATH_MAX PATH_MAX
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

#undef PTH_PATH_MAX

// =============================================================================

int main(void) {
    Path cwd = pth_cwd();
    printf("%s\n", cwd.str);
    return 0;
}

