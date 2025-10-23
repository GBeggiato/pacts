#include <stdio.h>

#include "pacts.c"

int main(void) {

    Path path = pth_cwd();
    pth_debug(&path);
    
    Path parent = pth_parent(&path);
    pth_debug(&parent);
    
    Path parent_resolved = pth_resolve(&parent);
    pth_debug(&parent_resolved);


    printf("\n");
    return 0;
}

