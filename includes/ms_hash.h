#ifndef MS_HASH_H
# define MS_HASH_H

# include <ms_struct.h>

# ifdef __x86_64
# define FNV_PRIME  0x100000001B3
# define FNV_OFFSET 0xCBF29CE484222325
# elif
# define FNV_PRIME  0x1000193
# define FNV_OFFSET 0x811C9DC5
# endif

size_t hash_fnv_onea(
	  unsigned char * key
	, size_t key_len
);

#endif /* !MS_HASH_H */

/* EOF */