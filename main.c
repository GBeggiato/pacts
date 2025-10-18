#include <stdio.h>

#include "pacts.c"

int main(void) {

    char *p = "/home/guido/Desktop/code/tracked/pacts/";
    Path path = pth_new(p);
    pth_debug(&path);
    
    Path parent = pth_parent(&path);
    pth_debug(&parent);

    printf("\n");
    return 0;
}

