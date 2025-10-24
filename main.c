#include <stdio.h>

#include "pacts.c"

#define UNUSED(x) (void) (x);

int main(void) {

    Path path            = pth_cwd();
    Path parent          = pth_parent(&path);
    Path parent_resolved = pth_resolve(&parent);
    Path joined          = pth_join(&parent_resolved, "here.c");

    pth_debug(&joined);


    printf("\n");
    return 0;
}

