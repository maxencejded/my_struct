#ifndef MS_DICT_H
# define MS_DICT_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif /* !MS_STRUCT_H */

#ifndef MS_CONTENT_H
#include <ms_content.h>
# endif /* !MS_CONTENT_H */

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_dict;

/* Type opaque */
typedef struct s_dict t_dict;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

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
int dict_init(
	  t_dict ** dict
	, size_t size
);

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
void dict_free(
	  t_dict * dict
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

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
int dict_insert(
	  t_dict * dict
	, void * data
	, size_t size
	, unsigned char * key
	, size_t key_len
	, size_t (*f_hash)(unsigned char * key, size_t key_len)
);

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
void *dict_search(
	  t_dict * dict
	, unsigned char * key
	, size_t key_len
	, size_t (*f_hash)(unsigned char * key, size_t key_len)
	, int (*f_compare)(void * data, unsigned char * key, size_t key_len)
);

#endif /* !MS_DICT_H */

/* EOF */