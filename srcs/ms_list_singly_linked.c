#include <ms_list_singly_linked.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_list_s
{
	void     * data;
	t_list_s * next;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_list_s * list_s_node(
	  void * data
	, size_t size
) {
	void     * copy;
	t_list_s * list;

	list = MS_CAST(t_list_s *, MS_ALLOC(sizeof(t_list_s)));
	if (MS_ADDRCK(list)) {
		MS_MEMSET(list, 0, sizeof(t_list_s));
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
	}
	return (list);
}

void list_s_destroy(
	  t_list_s ** list
	, void (*f_free)(void * data)
) {
	t_list_s * content;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
	) {
		while (MS_ADDRCK(*list))
		{
			content = *list;
			*list = (*list)->next;
			if (MS_ADDRCK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}
		*list = NULL;
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int list_s_is_empty(const t_list_s * list)
{
	if (MS_ADDRCK(list)) {
		if (MS_ADDRCK(list->data)) {
			return (0);
		}
	}
	return (1);
}

int list_s_fct(
	  t_list_s ** list
	, int (*f_fct)(void * data)
) {
	int        ret;
	t_list_s * content;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
		&& MS_ADDRCK(f_fct)
	) {
		content = *list;
		while (MS_ADDRCK(content)) {
			ret = f_fct(content->data);
			if (0 != ret) {
				return (ret);
			}
			content = content->next;
		}
	}
	return (0);
}

int list_s_push_front(
	  t_list_s ** list
	, void * data
	, size_t size
) {
	t_list_s * node;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(data)
	) {
		node = list_s_node(data, size);
		if (MS_ADDRCK(node)) {
			node->next = *list;
			*list = node;
			return (0);
		}
	}
	return (1);
}

int list_s_push_back(
	  t_list_s ** list
	, void * data
	, size_t size
) {
	t_list_s * tmp;
	t_list_s * node;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(data)
	) {
		node = list_s_node(data, size);
		if (MS_ADDRCK(node)) {
			if (MS_ADDRCK(*list)) {
				tmp = *list;
				while (MS_ADDRCK(tmp->next)) {
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

void * list_s_first_element(
	  t_list_s ** list
	, int flag
) {
	void     * data;
	t_list_s * node;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
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

void * list_s_last_element(
	  t_list_s ** list
	, int flag
) {
	void     * data;
	t_list_s * node;
	t_list_s * prev;

	if (
		   MS_ADDRCK(list)
		&& MS_ADDRCK(*list)
	) {
		if (MS_ADDRNULL((*list)->next)) {
			return (list_s_first_element(list, flag));
		}
		node = *list;
		prev = node;
		while (MS_ADDRCK(node->next)) {
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

void * list_s_nth_element(
	  t_list_s ** list
	, size_t n
	, int flag
) {
	void     * data;
	t_list_s * tmp;
	t_list_s * node;

	if (0 == n)
		return (list_s_first_element(list, flag));
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

/* EOF */