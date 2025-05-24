#ifndef OS_BASE_H
#define OS_BASE_H

#include "base/base.h"

void* os_memory_reserve(u64 size);
void  os_memory_commit(void* ptr, u64 size);
void  os_memory_decommit(void* ptr, u64 size);
void  os_memory_release(void* ptr, u64 size);

#endif /* end of include guard: OS_BASE_H */
