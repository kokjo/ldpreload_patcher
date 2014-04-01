#include "patcher.c"

void init() __attribute__ ((constructor));
int new_main(int argc, char **argv){
    printf("this is the new main!\n number of arguments: %d\n",argc);
}

void init() {
    hijack_function((void *)0x080483fd, new_main);
}


