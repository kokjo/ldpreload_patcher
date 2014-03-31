#include <sys/mman.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include "patcher.h"

int patch(void *address, void *patch, int patch_length, int mprotect_prot){
    int page_size = getpagesize();
    void *mprotect_address = (void *) ((int) address & ~page_size);
    int mprotect_length = ((int) address & page_size);
    int retval = mprotect(mprotect_address, mprotect_length, PROT_READ|PROT_WRITE);
    if(retval < 0){
        printf("mprotect returned %d before the patch, errno: %d\n", retval, errno); 
        return retval;
    }
    memcpy(address, patch, patch_length);
    retval = mprotect(mprotect_address, mprotect_length, mprotect_prot);
    if(retval < 0){
        printf("mprotect returned %d after the patch, errno: %d\n", retval, errno);
        return retval;
    }
    return 0;
}

int hijack_function(void *func, void *dest) {
    char the_patch[5] = {0};
    unsigned int *addr = (unsigned int *) &the_patch[1];
    the_patch[0] = 0xe9;
    *addr = (unsigned int)dest - (unsigned int)func - 5;
    return patch(func, the_patch, sizeof(the_patch), PROT_EXEC);
}
