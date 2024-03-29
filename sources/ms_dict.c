# include <ms_dict.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_dict
{
	size_t       size;
	size_t       (*f_hash)(unsigned char * key, size_t key_len);
	t_content ** content;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

int dict_init(
	  t_dict ** dict
	, size_t size
	, size_t (*f_hash)(unsigned char * key, size_t key_len)
) {
	size_t content_size;

	if (
		   MS_ADDRCK(dict)
		&& size > 0
		&& MS_ADDRCK(f_hash)
	) {
		*dict = MS_CAST(t_dict *, MS_ALLOC(sizeof(t_dict)));
		if (MS_ADDRCK(*dict)) {
			MS_MEMSET(*dict, 0, sizeof(t_dict));
			(*dict)->size    = size;
			(*dict)->f_hash  = f_hash;
			content_size     = size * sizeof(t_content *);
			(*dict)->content = MS_CAST(t_content **, MS_ALLOC(content_size));
			if (MS_ADDRCK((*dict)->content)) {
				MS_MEMSET((*dict)->content, 0, content_size);
				return (0);
			} else {
				MS_DEALLOC(*dict);
			}
		}
	}
	return (1);
}

void dict_destroy(
	  t_dict * dict
	, void (*f_free)(void * data)
) {
	size_t      i;
	t_content * content;

	if (MS_ADDRCK(dict)) {
		if (MS_ADDRCK(dict->content)) {
			i = 0;
			while (i < dict->size) {
				while (MS_ADDRCK(dict->content[i])) {
					content = dict->content[i];
					dict->content[i] = dict->content[i]->next;
					content_destroy(
						  content
						, f_free
					);
				}
				++i;
			}
			MS_DEALLOC(dict->content);
		}
		MS_DEALLOC(dict);
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int dict_insert(
	  t_dict * dict
	, void * data
	, size_t size
	, unsigned char * key
	, size_t key_len
) {
	size_t      i;
	t_content * content;

	if (
		   MS_ADDRCK(dict)
		&& MS_ADDRCK(data)
		&& MS_ADDRCK(key)
	) {
		content = content_init(data, size);
		if (MS_ADDRCK(content)) {
			i = dict->f_hash(key, key_len) % dict->size;
			if (MS_ADDRCK(dict->content[i])) {
				content->next = dict->content[i];
			}
			dict->content[i] = content;
			return (0);
		}
	}
	return (1);
}

void * dict_search(
	  t_dict * dict
	, unsigned char * key
	, size_t key_len
	, int flag
	, int (*f_compare)(void * data, unsigned char * key, size_t key_len)
) {
	size_t      i;
	void      * data;
	t_content * tmp;
	t_content * content;

	data = NULL;
	if (
		   MS_ADDRCK(dict)
		&& MS_ADDRCK(key)
		&& MS_ADDRCK(f_compare)
	) {
		i = dict->f_hash(key, key_len) % dict->size;
		if (MS_ADDRCK(dict->content[i])) {
			if (MS_ADDRNULL((dict->content[i])->next)) {
				if (0 == f_compare((dict->content[i])->data, key, key_len)) {
					data = (dict->content[i])->data;
					if (MS_ELEMENT_REMOVE == flag) {
						content_destroy(
							  dict->content[i]
							, NULL
						);
						dict->content[i] = NULL;
					}
				}
			} else {
				content = dict->content[i];
				if (0 == f_compare(content->data, key, key_len)) {
					data = content->data;
					if (MS_ELEMENT_REMOVE == flag) {
						dict->content[i] = content->next;
						content_destroy(
							  content
							, NULL
						);
					}
				} else {
					tmp = content->next;
					while (MS_ADDRCK(tmp)) {
						if (0 == f_compare(tmp->data, key, key_len)) {
							data = tmp->data;
							if (MS_ELEMENT_REMOVE == flag) {
								content->next = tmp->next;
								content_destroy(
									  tmp
									, NULL
								);
							}
						}
						content = content->next;
						tmp     = content->next;
					}
				}
			}
		}
	}
	return (data);
}

/* EOF */