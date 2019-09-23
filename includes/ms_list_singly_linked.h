#ifndef MS_LIST_SINGLY_LINKED_H
# define MS_LIST_SINGLY_LINKED_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_list_s
{
	void				*data;
	struct s_list_s		*next;
}						t_list_s;

/*! Singly-linked List node init
 *
 * @brief Create a node for the singly-linked list
 *
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
static inline
t_list_s		*list_s_node(void *data)
{
	t_list_s	*list;

	list = MS_CAST(t_list_s *, MS_ALLOC(sizeof(t_list_s)));
	if (MS_ADDRK(list)) {
		MS_MEMSET(list, 0, sizeof(t_list_s));
		list->data = data;
	}
	return (list);
}

/*! Singly-linked List free
 *
 * @brief Dealloc an singly-linked list
 *
 * @param list
 *     (input) singly-linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
static inline
void			list_s_free(
	  t_list_s **list
	, void (*f_free)(void *data)
) {
	t_list_s	*content;

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

/*! Singly-linked is empty
 *
 * @brief Check if the singly-linked list is empty
 *
 * @param list
 *     (input) singly-linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
int			list_s_is_empty(t_list_s *list)
{
	if (MS_ADDRK(list)) {
		if (MS_ADDRK(list->data)) {
			return (0);
		}
	}
	return (1);
}

/*! Singly-linked List size
 *
 * @brief Count the number of elements in the list
 *
 * @param list
 *     (input) singly-linked list
 *
 * @result If successful, the size is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
size_t		list_s_size(t_list_s *list)
{
	size_t		size;

	size = 0;
	while (MS_ADDRK(list)) {
		list = list->next;
		++size;
	}
	return (size);
}

/*! Singly-linked List function
 *
 * @brief Apply a function to each nodes of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
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
int				list_s_fct(
	  t_list_s **list
	, int (*f_fct)(void *data)
) {
	int         ret;
	t_list_s	*content;

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

/*! Singly-linked List push front
 *
 * @brief Push an element on top of singly-linked list
 *
 * @param list
 *     (input) address of the singly-linked list
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			list_s_push_front(
	  t_list_s **list
	, void *data
) {
	t_list_s	*node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(data)
	) {
		node = list_s_node(data);
		if (MS_ADDRK(node)) {
			node->next = *list;
			*list = node;
			return (0);
		}
	}
	return (1);
}

/*! Singly-linked List push back
 *
 * @brief Push an element at the bottom of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			list_s_push_back(
	  t_list_s **list
	, void *data
) {
	t_list_s	*tmp;
	t_list_s	*node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(data)
	) {
		node = list_s_node(data);
		if (MS_ADDRK(node)) {
			if (MS_ADDRK(*list)) {
				tmp = *list;
				while (MS_ADDRK(tmp->next)) {
					tmp = tmp->next;
				}
				tmp->next = node;
			} else {
				*list = node;
			}
			return (0);
		}
	}
	return (1);
}

/*! Singly-linked List first element
 *
 * @brief Return the first element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_s_first_element(
	  t_list_s **list
	, int flag
) {
	void		*data;
	t_list_s	*node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		node = *list;
		data = node->data;
		if (MS_ELEMENT_REMOVE & flag) {
			*list = node->next;
			MS_DEALLOC(node);
		}
		return (data);
	}
	return (NULL);
}

/*! Singly-linked List last element
 *
 * @brief Return the last element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_s_last_element(
	  t_list_s **list
	, int flag
) {
	void     *data;
	t_list_s *node;
	t_list_s *prev;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		if (MS_NULL((*list)->next)) {
			return (list_s_first_element(list, flag));
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

/*! Singly-linked List n-th element
 *
 * @brief Return the n-th element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_s_nth_element(
	  t_list_s **list
	, size_t n
	, int flag
) {
	void		*data;
	t_list_s	*tmp;
	t_list_s	*node;

	if (0 == n)
		return (list_s_first_element(list, flag));
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