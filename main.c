#include <stdio.h>

#define PTH_IMPLEMENTATION
#include "pacts.h"

// #define UNUSED(x) (void) (x);

int main(void) {

    Path path = pth_cwd();

    pth_parent(&path);
    pth_join(&path, "pacts");
    pth_join(&path, "pacts.h");
    pth_suffix_change(&path, ".html");
    pth_debug(&path);
    
    return 0;
}
