#include <ms_content.h>

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

t_content * content_init(
	  void * data
	, size_t size
) {
	void      * copy;
	t_content * content;

	content = MS_CAST(t_content *, MS_ALLOC(sizeof(t_content)));
	if (MS_ADDRCK(content)) {
		if (0 == size) {
			content->data = data;
		} else {
			copy = MS_ALLOC(size);
			if (MS_ADDRCK(copy)) {
				MS_MEMCPY(copy, data, size);
				content->data = copy;
			} else {
				MS_DEALLOC(content);
				return (NULL);
			}
		}
		content->next = NULL;
	}
	return (content);
}

/* EOF */