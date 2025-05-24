#include "os.h"

#ifdef OS_LINUX
#	include "impl/linux_os.c"
#else
#	error "Not implemented yet"
#endif /* ifdef OS_LINUX */
