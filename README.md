
# Pacts
### Paths in C

the general idea is Pathlib from python

goals are: 
- intuitive api
- no memory management and no stateful library
- stdio.h ease of interaction

## current status

basic working state, provided you start from "pth_cwd" and find the relative
paths from there or instantiate a Path from a const char * that you know
exists.

## what's missing

wrappers around <dirent.h> functionality (you still can use path.str as an
argument to those functions)
