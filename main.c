#include <stdio.h>

#define PTH_IMPLEMENTATION
#include "pacts.h"

// #define UNUSED(x) (void) (x);

int main(void) {

    Path path = pth_cwd();
    pth_debug(&path);

    pth_parent(&path);
    pth_debug(&path);

    pth_join(&path, "pacts");
    pth_join(&path, "pacts.c");
    pth_debug(&path);
    
    return 0;
}
