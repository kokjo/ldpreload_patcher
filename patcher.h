#ifndef _PATCHER_H_
#define _PATCHER_H_
#include <sys/mman.h>
int patch(void *address, void *patch, int patch_lenth, int mmap_prot);
int hijack_function(void *func, void *replacement);

#endif
