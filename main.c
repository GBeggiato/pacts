#include <stdio.h>

#include "pacts.c"

// #define UNUSED(x) (void) (x);

int main(void) {

    Path path = pth_cwd();
    int e = pth_exists(&path);
    int d = pth_is_dir(&path);
    int f = pth_is_file(&path); 
    pth_debug(&path);
    printf("exists = %d, is_dir = %d, is_file = %d\n\n", e, d, f);

    Path the_file = pth_copy(&path);
    pth_join(&the_file, "here.c");
    e = pth_exists(&the_file);
    d = pth_is_dir(&the_file);
    f = pth_is_file(&the_file); 
    pth_debug(&the_file);
    printf("exists = %d, is_dir = %d, is_file = %d\n\n", e, d, f);

    pth_parent(&the_file);
    pth_join(&the_file, "pacts.c");
    e = pth_exists(&the_file);
    d = pth_is_dir(&the_file);
    f = pth_is_file(&the_file); 
    pth_debug(&the_file);
    printf("exists = %d, is_dir = %d, is_file = %d\n\n", e, d, f);
    
    printf("\n");
    return 0;
}

