#ifndef MS_DICT_H
# define MS_DICT_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_dict
{
	size_t				size;
	t_content			**content;
}						t_dict;

/*! Dictionary init
 *
 * @brief Initialize a dictionary of a given size
 *
 * @param dict
 *     (input) dict to initialize
 * @param size
 *     (input) size of the dictionary
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int		dict_init(
	  t_dict **dict
	, size_t size
) {
	size_t	content_size;

	if (MS_ADDRK(dict)) {
		*dict = MS_CAST(t_dict *, MS_ALLOC(sizeof(t_dict)));
		if (MS_ADDRK(*dict)) {
			MS_MEMSET(*dict, 0, sizeof(t_dict));
			(*dict)->size = size;
			content_size = size * sizeof(t_content *);
			(*dict)->content = MS_CAST(t_content **, MS_ALLOC(content_size));
			if (MS_NULL((*dict)->content)) {
				MS_DEALLOC(*dict);
				return (1);
			}
			MS_MEMSET((*dict)->content, 0, content_size);
			return (0);
		}
	}
	return (1);
}

/*! Dictionary free
 *
 * @brief Dealloc a dictionary
 *
 * @param dict
 *     (input) dictionary to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN
*/
static inline
void		dict_free(
	  t_dict *dict
	, void (*f_free)(void *data)
) {
	size_t    i;
	t_content *content;

	if (MS_ADDRK(dict)) {
		i = 0;
		while (i < dict->size) {
			while (MS_ADDRK(dict->content[i])) {
				content = dict->content[i];
				dict->content[i] = dict->content[i]->next;
				if (MS_ADDRK(f_free)) {
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

/*! Dictionary insert
 *
 * @brief Insert an element into the dictionary
 *
 * @param dict
 *     (input) dictionary
 * @param data
 *     (input) data to add to the dictionary
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 * @param key
 *     (input) key to use
 * @param key_len
 *     (input) length of the key
 * @param f_hash
 *     (input) function use to create the hash
 *             @param key
 *                 (input) key to hash
 *             @param key_len
 *                 (input) length of the key
 *
 *             @result Return a fresh hash
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			dict_insert(
	  t_dict *dict
	, void *data
	, size_t size
	, unsigned char *key
	, size_t key_len
	, size_t (*f_hash)(unsigned char *key, size_t key_len)
) {
	size_t		i;
	t_content	*content;

	if (
		   MS_ADDRK(dict)
		&& MS_ADDRK(data)
		&& MS_ADDRK(key)
		&& MS_ADDRK(f_hash)
	) {
		content = content_init(data, size);
		if (MS_ADDRK(content)) {
			i = f_hash(key, key_len) % dict->size;
			if (MS_ADDRK(dict->content[i])) {
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

/*! Dictionary search
 *
 * @brief Search an element into the dictionary
 *
 * @param dict
 *     (input) dictionary
 * @param data
 *     (input) data to add to the dictionary
 * @param key
 *     (input) key to use
 * @param key_len
 *     (input) length of the key
 * @param f_hash
 *     (input) function use to create the hash
 *             @param key
 *                 (input) key to hash
 *             @param key_len
 *                 (input) length of the key
 *
 *             @result Return a fresh hash
 * @param f_compare
 *     (input) function use to compare the key with the data
 *             @param data
 *                 (input) data to compare
 *             @param key
 *                 (input) key to compare
 *             @param key_len
 *                 (input) length of the key
 *
 *             @result If equals, 0 is returned.
 *                     If greater, 1 is returned.
 *                     If smaller, -1 is returned.
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
static inline
void		*dict_search(
	  t_dict *dict
	, unsigned char *key
	, size_t key_len
	, size_t (*f_hash)(unsigned char *key, size_t key_len)
	, int (*f_compare)(void *data, unsigned char *key, size_t key_len)
) {
	size_t		i;
	t_content	*content;

	if (
		   MS_ADDRK(dict)
		&& MS_ADDRK(key)
		&& MS_ADDRK(f_hash)
		&& MS_ADDRK(f_compare)
	) {
		i = f_hash(key, key_len) % dict->size;
		content = dict->content[i];
		if (MS_ADDRK(content)) {
			if (MS_NULL(content->next)) {
				if (0 == f_compare(content->data, key, key_len)) {
					return (content->data);
				}
			} else {
				while(MS_ADDRK(content)) {
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

#endif