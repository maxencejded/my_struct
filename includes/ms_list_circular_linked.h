#ifndef MS_LIST_CIRCULAR_H
# define MS_LIST_CIRCULAR_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_list_c
{
	void				*data;
	struct s_list_c		*prev;
	struct s_list_c		*next;
}						t_list_c;

/*! Circular Linked List node init
 *
 * @brief Create a node for the circular linked list
 *
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
static inline
t_list_c		*list_c_node(void *data)
{
	t_list_c	*list;

	list = MS_CAST(t_list_c *, MS_ALLOC(sizeof(t_list_c)));
	if (MS_ADDRK(list)) {
		MS_MEMSET(list, 0, sizeof(t_list_c));
		list->data = data;
		list->prev = NULL;
		list->next = NULL;
	}
	return (list);
}

/*! Circular Linked List free
 *
 * @brief Dealloc an circular linked list
 *
 * @param list
 *     (input) circular linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
static inline
void			list_c_free(
	  t_list_c **list
	, void (*f_free)(void *data)
) {
	t_list_c	*first;
	t_list_c	*content;

	if (MS_ADDRK(list)) {
		first = *list;
		if (MS_ADDRK(*list)) {
			*list = first->next;
			while (first != *list)
			{
				content = *list;
				*list = (*list)->next;
				if (MS_ADDRK(f_free)) {
					f_free(content->data);
				}
				MS_DEALLOC(content);
			}
		}
		MS_DEALLOC(first);
		*list = NULL;
	}
}

/*! Circular Linked is empty
 *
 * @brief Check if the circular linked list is empty
 *
 * @param list
 *     (input) circular linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
int			list_c_is_empty(t_list_c *list)
{
	if (MS_ADDRK(list)) {
		if (MS_ADDRK(list->data)) {
			return (0);
		}
	}
	return (1);
}

/*! Circular Linked List size
 *
 * @brief Count the number of elements in the list
 *
 * @param list
 *     (input) circular linked list
 *
 * @result If successful, the size is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
size_t		list_c_size(t_list_c *list)
{
	size_t		size;
	t_list_c	*first;

	size = 0;
	first = list;
	if (MS_ADDRK(first)) {
		++size;
		list = first->next;
		while (first != list)
		{
			list = list->next;
			++size;
		}
	}
	return (size);
}

/*! Circular Linked List function
 *
 * @brief Apply a function to each nodes of circular linked list
 *
 * @param list
 *     (input) circular linked list
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
int				list_c_fct(
	  t_list_c **list
	, int (*f_fct)(void *data)
) {
	int         ret;
	t_list_c	*first;
	t_list_c	*content;

	if (
		MS_ADDRK(list)
		&& MS_ADDRK(f_fct)
	) {
		first = *list;
		if (MS_ADDRK(*list)) {
			ret = f_fct(first->data);
			if (0 != ret) {
				return (ret);
			}
			*list = first->next;
			while (first != *list)
			{
				content = *list;
				*list = (*list)->next;
				ret = f_fct(content->data);
				if (0 != ret) {
					return (ret);
				}
			}
		}
	}
	return (0);
}

/*! Circular Linked List push
 *
 * @brief Push an element on the circular linked list
 *
 * @param list
 *     (input) address of the circular linked list
 * @param data
 *     (input) data to add to the list
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			list_c_push(
	  t_list_c **list
	, void *data
) {
	t_list_c	*node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(data)
	) {
		node = list_c_node(data);
		if (MS_ADDRK(node)) {
			if (MS_ADDRK(*list)) {
				if (NULL == (*list)->next) {
					node->next = *list;
					node->prev = *list;
					(*list)->next = node;
					(*list)->prev = node;
				} else {
					node->next = *list;
					node->prev = (*list)->prev;
					(*list)->prev = node;
					node->prev->next = node;
				}
			}
			*list = node;
			return (0);
		}
	}
	return (1);
}

/*! Circular Linked List first element
 *
 * @brief Return the first element of circular linked list
 *
 * @param list
 *     (input) circular linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_c_element(
	  t_list_c **list
	, int flag
) {
	void		*data;
	t_list_c	*node;

	if (
		   MS_ADDRK(list)
		&& MS_ADDRK(*list)
	) {
		node = *list;
		data = node->data;
		if (MS_ELEMENT_REMOVE & flag) {
			*list = node->next;
			if (node == *list) {
				*list = NULL;
			} else {
				(*list)->prev = node->prev;
				(*list)->prev->next = *list;
			}
			MS_DEALLOC(node);
		}
		return (data);
	}
	return (NULL);
}

/*! Circular Linked List n-th element
 *
 * @brief Return the n-th element of circular linked list
 *
 * @param list
 *     (input) circular linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @note The n-th element can be the first element of the list
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*list_c_nth_element(
	  t_list_c **list
	, size_t n
	, int flag
) {
	void		*data;
	t_list_c	*tmp;
	t_list_c	*node;

	if (0 == n)
		return (list_c_element(list, flag));
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
					node->next = tmp->next;
					tmp->next->prev = node;
					if (tmp == *list) {
						if (tmp->next == *list) {
							*list = NULL;
						} else {
							*list = node->next;
						}
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