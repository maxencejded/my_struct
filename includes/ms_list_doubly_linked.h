#ifndef MS_LIST_DOUBLY_LINKED_H
# define MS_LIST_DOUBLY_LINKED_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_list_d
{
	void				*data;
	struct s_list_d		*prev;
	struct s_list_d		*next;
}						t_list_d;

/*! Doubly-linked List node init
 *
 * @brief Create a node for the doubly-linked list
 *
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
static inline
t_list_d		*list_d_node(void *data)
{
	t_list_d *list;

	list = MS_CAST(t_list_d *, MS_ALLOC(sizeof(t_list_d)));
	if (MS_ADDRK(list)) {
		MS_MEMSET(list, 0, sizeof(t_list_d));
		list->data = data;
	}
	return (list);
}

/*! Doubly-linked List free
 *
 * @brief Dealloc an doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
static inline
void			list_d_free(
	  t_list_d **list
	, void (*f_free)(void *data)
) {
	t_list_d *content;

	if (MS_ADDRK(list)) {
		while (MS_ADDRK(*list))
		{
			content = *list;
			*list = (*list)->next;
			if (MS_ADDRK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}
		*list = NULL;
	}
}

/*! Doubly-linked List is empty
 *
 * @brief Check if the doubly-linked list is empty
 *
 * @param list
 *     (input) doubly-linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
int			list_d_is_empty(t_list_d *list)
{
	if (MS_ADDRK(list)) {
		if (MS_ADDRK(list->data)) {
			return (0);
		}
	}
	return (1);
}

/*! Doubly-linked List size
 *
 * @brief Count the number of elements in the list
 *
 * @param list
 *     (input) doubly-linked list
 *
 * @result If successful, the size is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
size_t		list_d_size(t_list_d *list)
{
	size_t		size;

	size = 0;
	while (MS_ADDRK(list)) {
		list = list->next;
		++size;
	}
	return (size);
}

/*! Doubly-linked List function
 *
 * @brief Apply a function to each nodes of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
static inline
int				list_d_fct(
	  t_list_d **list
	, int (*f_fct)(void *data)
) {
	int         ret;
	t_list_d	*content;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(f_fct)
	) {
		while (MS_ADDRK(*list))
		{
			content = *list;
			*list = (*list)->next;
			ret = f_fct(content->data);
			if (0 != ret) {
				return (ret);
			}
		}
	}
	return (0);
}

/*! Doubly-linked List push front
 *
 * @brief Push an element on top of doubly-linked list
 *
 * @param list
 *     (input) address of the doubly-linked list
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			list_d_push_front(
	  t_list_d **list
	, void *data
) {
	t_list_d *node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(data)
	) {
		node = list_d_node(data);
		if (MS_ADDRK(node)) {
			if (MS_ADDRK(*list)) {
				(*list)->prev = node;
			}
			node->next = *list;
			*list = node;
			return (0);
		}
	}
	return (1);
}

/*! Doubly-linked List push back
 *
 * @brief Push an element at the bottom of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			list_d_push_back(
	  t_list_d **list
	, void *data
) {
	t_list_d *tmp;
	t_list_d *node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(data)
	) {
		node = list_d_node(data);
		if (MS_ADDRK(node)) {
			if (MS_ADDRK(*list)) {
				tmp = *list;
				while (MS_ADDRK(tmp->next)) {
					tmp = tmp->next;
				}
				tmp->next = node;
				node->prev = tmp;
			} else {
				*list = node;
			}
			return (0);
		}
	}
	return (1);
}

/*! Doubly-linked List first element
 *
 * @brief Return the first element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_d_first_element(
	  t_list_d **list
	, int flag
) {
	void     *data;
	t_list_d *node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		node = *list;
		data = node->data;
		if (MS_ELEMENT_REMOVE & flag) {
			*list = node->next;
			if (MS_ADDRK(*list)) {
				(*list)->prev = NULL;
			}
			MS_DEALLOC(node);
		}
		return (data);
	}
	return (NULL);
}

/*! Doubly-linked List last element
 *
 * @brief Return the last element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_d_last_element(
	  t_list_d **list
	, int flag
) {
	void     *data;
	t_list_d *node;
	t_list_d *prev;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		if (MS_NULL((*list)->next)) {
			return (list_d_first_element(list, flag));
		}
		node = *list;
		prev = node;
		while (MS_ADDRK(node->next)) {
			prev = node;
			node = node->next;
		}
		data = node->data;
		if (MS_ELEMENT_REMOVE & flag) {
			prev->next = NULL;
			MS_DEALLOC(node);
		}
		return (data);
	}
	return (NULL);
}

/*! Doubly-linked List n-th element
 *
 * @brief Return the n-th element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_d_nth_element(
	  t_list_d **list
	, size_t n
	, int flag
) {
	void     *data;
	t_list_d *tmp;
	t_list_d *node;

	if (0 == n)
		return (list_d_first_element(list, flag));
	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		node = *list;
		while (MS_ADDRK(node->next) && n) {
			if (1 == n) {
				data = node->next->data;
				if (MS_ELEMENT_REMOVE & flag) {
					tmp = node->next;
					node->next = node->next->next;
					if (MS_ADDRK(node->next)) {
						node->next->prev = node;
					}
					MS_DEALLOC(tmp);
				}
				return (data);
			}
			node = node->next;
			--n;
		}
	}
	return (NULL);
}

#endif