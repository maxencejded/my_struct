#ifndef MS_HASH_H
# define MS_HASH_H

# include <stdlib.h>

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

# ifdef __x86_64
# define FNV_PRIME  0x100000001B3
# define FNV_OFFSET 0xCBF29CE484222325
# elif
# define FNV_PRIME  0x1000193
# define FNV_OFFSET 0x811C9DC5
# endif

size_t			hash_fnv_onea(unsigned char *key, size_t key_len)
{
	size_t	i;
	size_t	hash;

	hash = MS_CAST(size_t, FNV_OFFSET);
	i = 0;
	while (i < key_len)
	{
		hash ^= MS_CAST(size_t, key[i]);
		hash *= MS_CAST(size_t, FNV_PRIME);
		++i;
	}
	return (hash);
}

#endif