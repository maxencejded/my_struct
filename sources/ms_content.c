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
			content->next = NULL;
		} else {
			copy = MS_ALLOC(size);
			if (MS_ADDRCK(copy)) {
				MS_MEMCPY(copy, data, size);
				content->data = copy;
				content->next = NULL;
			} else {
				MS_DEALLOC(content);
				content = NULL;
			}
		}
	}
	return (content);
}

void content_destroy(
	  t_content * content
	, void (*f_free)(void * data)
) {
	if (MS_ADDRCK(content)) {
		if (MS_ADDRCK(f_free)) {
			f_free(content->data);
		}
		MS_DEALLOC(content);
	}
}

/* EOF */