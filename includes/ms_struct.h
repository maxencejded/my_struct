#ifndef MS_STRUCT_H
# define MS_STRUCT_H

# include <stdlib.h>
# include <string.h>

/*
 * System functions
*/
# define __SYS_MEMSET(dst, c, size)  memset(dst, c, size)
# define __SYS_MALLOC(size)          malloc(size)
# define __SYS_DEALLOC(addr)         free(addr)
# define __SYS_CAST(type, content)   (type)content
# define __SYS_UNUSED(content)       (void)content

/*
 * MS_STRUCT specific define
*/
# define MS_NULL(addr)    		     (addr == NULL) ? 1 : 0
# define MS_ADDRK(addr)   		     (addr == NULL) ? 0 : 1
# define MS_CAST(type, content)      __SYS_CAST(type, content)
# define MS_UNUSED(content)          __SYS_UNUSED(content)
# define MS_ALLOC(size)   		     __SYS_MALLOC(size)
# define MS_DEALLOC(addr) 		     __SYS_DEALLOC(addr)
# define MS_MEMSET(dst, c, size)     __SYS_MEMSET(dst, c, size)

# define MS_ELEMENT_REMOVE           MS_CAST(int, 0x01)

/*
 * MS_LIST_SINGLY_LINKED:
 *     Singly-linked list fuctions.
*/
# include <ms_list_singly_linked.h>

/*
 * MS_LIST_DOUBLY_LINKED:
 *     Doubly-linked list fuctions.
*/
# include <ms_list_doubly_linked.h>

/*
 * MS_LIST_CIRCULAR_LINKED:
 *     Circular Linked list fuctions.
*/
# include <ms_list_circular_linked.h>

#endif