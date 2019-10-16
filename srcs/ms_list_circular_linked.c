# include <ms_list_circular_linked.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_list_c
{
	void     * data;
	t_list_c * prev;
	t_list_c * next;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_list_c *list_c_node(
	  void * data
	, size_t size
) {
	void     * copy;
	t_list_c * list;

	list = MS_CAST(t_list_c *, MS_ALLOC(sizeof(t_list_c)));
	if (MS_ADDRCK(list)) {
		MS_MEMSET(list, 0, sizeof(t_list_c));
		if (0 == size) {
			list->data = data;
		} else {
			copy = MS_ALLOC(size);
			if (MS_ADDRCK(copy)) {
				MS_MEMCPY(copy, data, size);
				list->data = copy;
			} else {
				MS_DEALLOC(list);
				return (NULL);
			}
		}
		list->next = NULL;
		list->prev = NULL;
	}
	return (list);
}

void list_c_free(
	  t_list_c **list
	, void (*f_free)(void *data)
) {
	t_list_c	*first;
	t_list_c	*content;

	if (MS_ADDRCK(list)) {
		first = *list;
		if (MS_ADDRCK(*list)) {
			*list = first->next;
			while (
				   MS_ADDRCK(*list)
				&& first != *list
			) {
				content = *list;
				*list = (*list)->next;
				if (MS_ADDRCK(f_free)) {
					f_free(content->data);
				}
				MS_DEALLOC(content);
			}
		}
		MS_DEALLOC(first);
		*list = NULL;
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int list_c_is_empty(const t_list_c * list)
{
	if (MS_ADDRCK(list)) {
		if (MS_ADDRCK(list->data)) {
			return (0);
		}
	}
	return (1);
}

int list_c_fct(
	  t_list_c ** list
	, int (*f_fct)(void * data)
) {
	int        ret;
	t_list_c * first;
	t_list_c * content;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
		&& MS_ADDRCK(f_fct)
	) {
		if (MS_ADDRCK(*list)) {
			first = *list;
			ret = f_fct(first->data);
			if (0 != ret) {
				return (ret);
			}
			content = (*list)->next;;
			while (
				   MS_ADDRCK(content)
				&& first != content
			) {
				ret = f_fct(content->data);
				if (0 != ret) {
					return (ret);
				}
				content = content->next;
			}
		}
	}
	return (0);
}

int list_c_push(
	  t_list_c ** list
	, void * data
	, size_t size
) {
	t_list_c * node;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(data)
	) {
		node = list_c_node(data, size);
		if (MS_ADDRCK(node)) {
			if (MS_ADDRCK(*list)) {
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

void *list_c_element(
	  t_list_c ** list
	, int flag
) {
	void     * data;
	t_list_c * node;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
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

void *list_c_nth_element(
	  t_list_c ** list
	, size_t n
	, int flag
) {
	void     * data;
	t_list_c * tmp;
	t_list_c * node;

	if (0 == n)
		return (list_c_element(list, flag));
	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
	) {
		node = *list;
		while (MS_ADDRCK(node->next) && n) {
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

/* EOF */