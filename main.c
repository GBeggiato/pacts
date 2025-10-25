#include <stdio.h>

#include "pacts.c"

// #define UNUSED(x) (void) (x);

int main(void) {

    Path path = pth_cwd();
    pth_debug(&path);
    pth_parent(&path);
    pth_debug(&path);
    
    printf("\n");
    return 0;
}
