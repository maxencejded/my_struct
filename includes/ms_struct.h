#ifndef MS_STRUCT_H
# define MS_STRUCT_H

# include <stdlib.h>
# include <string.h>

/*
 * System functions
*/
# define __SYS_MEMSET(dst, c, size)   memset(dst, c, size)
# define __SYS_MEMCPY(dst, src, size) memcpy(dst, src, size)
# define __SYS_MALLOC(size)           malloc(size)
# define __SYS_DEALLOC(addr)          free(addr)
# define __SYS_CAST(type, content)    (type)content
# define __SYS_UNUSED(content)        (void)content

/*
 * MS_STRUCT specific define
*/
# define MS_NULL(addr)                (addr == NULL) ? 1 : 0
# define MS_ADDRCK(addr)              (addr == NULL) ? 0 : 1
# define MS_CAST(type, content)       __SYS_CAST(type, content)
# define MS_UNUSED(content)           __SYS_UNUSED(content)
# define MS_ALLOC(size)               __SYS_MALLOC(size)
# define MS_DEALLOC(addr)             __SYS_DEALLOC(addr)
# define MS_MEMSET(dst, c, size)      __SYS_MEMSET(dst, c, size)
# define MS_MEMCPY(dst, src, size)    __SYS_MEMCPY(dst, src, size)

# define MS_ELEMENT_REMOVE            MS_CAST(int, 0x01)

#endif