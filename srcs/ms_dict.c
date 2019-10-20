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
		   size > 0
		&& MS_ADDRCK(dict)
		&& MS_ADDRCK(f_hash)
	) {
		*dict = MS_CAST(t_dict *, MS_ALLOC(sizeof(t_dict)));
		if (MS_ADDRCK(*dict)) {
			MS_MEMSET(*dict, 0, sizeof(t_dict));
			(*dict)->size = size;
			(*dict)->f_hash = f_hash;
			content_size = size * sizeof(t_content *);
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

void dict_free(
	  t_dict * dict
	, void (*f_free)(void * data)
) {
	size_t      i;
	t_content * content;

	if (MS_ADDRCK(dict)) {
		i = 0;
		while (i < dict->size) {
			while (MS_ADDRCK(dict->content[i])) {
				content = dict->content[i];
				dict->content[i] = dict->content[i]->next;
				if (MS_ADDRCK(f_free)) {
					f_free(content->data);
				}
				MS_DEALLOC(content);
			}
			++i;
		}
		MS_DEALLOC(dict->content);
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
				dict->content[i] = content;
			} else {
				dict->content[i] = content;
			}
			return (0);
		}
	}
	return (1);
}

void * dict_search(
	  t_dict * dict
	, unsigned char * key
	, size_t key_len
	, int (*f_compare)(void * data, unsigned char * key, size_t key_len)
) {
	size_t      i;
	t_content * content;

	if (
		   MS_ADDRCK(dict)
		&& MS_ADDRCK(key)
		&& MS_ADDRCK(f_compare)
	) {
		i = dict->f_hash(key, key_len) % dict->size;
		content = dict->content[i];
		if (MS_ADDRCK(content)) {
			if (MS_ADDRNULL(content->next)) {
				if (0 == f_compare(content->data, key, key_len)) {
					return (content->data);
				}
			} else {
				while(MS_ADDRCK(content)) {
					if (0 == f_compare(content->data, key, key_len)) {
						return (content->data);
					}
					content = content->next;
				}
			}
		}
	}
	return (NULL);
}

/* EOF */