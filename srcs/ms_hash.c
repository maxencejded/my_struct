#include <ms_hash.h>

size_t hash_fnv_onea(
	  unsigned char * key
	, size_t key_len
) {
	size_t i;
	size_t hash;

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

/* EOF */