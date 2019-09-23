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
# define MS_ADDRK(addr)               (addr == NULL) ? 0 : 1
# define MS_CAST(type, content)       __SYS_CAST(type, content)
# define MS_UNUSED(content)           __SYS_UNUSED(content)
# define MS_ALLOC(size)               __SYS_MALLOC(size)
# define MS_DEALLOC(addr)             __SYS_DEALLOC(addr)
# define MS_MEMSET(dst, c, size)      __SYS_MEMSET(dst, c, size)
# define MS_MEMCPY(dst, src, size)    __SYS_MEMCPY(dst, src, size)

# define MS_ELEMENT_REMOVE            MS_CAST(int, 0x01)

typedef struct			s_content
{
	void				*data;
	struct s_content	*next;
}						t_content;

/*! Content init
 *
 * @brief Initialize a content
 *
 * @param data
 *     (input) data to add to the structure
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result Return a new content.
*/
static inline
t_content	*content_init(
	  void *data
	, size_t size
) {
	void      *copy;
	t_content *content;

	content = MS_CAST(t_content *, MS_ALLOC(sizeof(t_content)));
	if (MS_ADDRK(content)) {
		if (0 == size) {
			content->data = data;
		} else {
			copy = MS_ALLOC(size);
			if (MS_ADDRK(copy)) {
				MS_MEMCPY(copy, data, size);
				content->data = copy;
			} else {
				MS_DEALLOC(content);
				return (NULL);
			}
		}
		content->next = NULL;
	}
	return (content);
}

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

/*
 * MS_STACK:
 *     Stack fuctions.
*/
# include <ms_stack.h>

/*
 * MS_QUEUE:
 *     Queue fuctions.
*/
# include <ms_queue.h>

/*
 * MS_DICT:
 *     Dictionary functions
*/
# include <ms_dict.h>

/*
 * MS_HASH:
 *     Hashing functions
*/
# include <ms_hash.h>

/*
 * MS_TREE:
 *     Tree functions
*/
# include <ms_tree.h>

#endif