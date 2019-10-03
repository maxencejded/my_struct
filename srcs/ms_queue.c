#include <ms_queue.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_queue
{
	t_content * first;
	t_content * last;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

int queue_init(t_queue ** queue)
{
	if (MS_ADDRCK(queue)) {
		*queue = MS_CAST(t_queue *, MS_ALLOC(sizeof(t_queue)));
		if (MS_ADDRCK(*queue)) {
			MS_MEMSET(*queue, 0, sizeof(t_queue));
			return (0);
		}
	}
	return (1);
}

void queue_free(
	  t_queue * queue
	, void (*f_free)(void * data)
) {
	t_content * content;

	if (MS_ADDRCK(queue)) {
		while (MS_ADDRCK(queue->first))
		{
			content = queue->first;
			queue->first = queue->first->next;
			if (MS_ADDRCK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}		
		MS_DEALLOC(queue);
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int queue_is_empty(const t_queue * queue)
{
	if (MS_ADDRCK(queue)) {
		if (MS_ADDRCK(queue->first)) {
			return (0);
		}
	}
	return (1);
}

int queue_enqueue(
	  t_queue * queue
	, void * data
	, size_t size
) {
	t_content * content;

	if (
		   MS_ADDRCK(queue)
		&& MS_ADDRCK(data)
	) {
		content = content_init(data, size);
		if (MS_ADDRCK(content)) {
			if (MS_ADDRCK(queue->last)) {
				queue->last->next = content;
			} else {
				queue->first = content;
			}
			queue->last = content;
			return (0);
		}
	}
	return (1);
}

void *queue_dequeue(t_queue * queue)
{
	void      * data;
	t_content * content;

	if (MS_ADDRCK(queue)) {
		content = queue->first;
		if (MS_ADDRCK(content)) {
			queue->first = queue->first->next;
			if (content == queue->last) {
				queue->last = NULL;
			}
			data = content->data;
			MS_DEALLOC(content);
			return (data);
		}
	}
	return (NULL);
}

void *queue_peek(t_queue * queue)
{
	if (MS_ADDRCK(queue)) {
		if (MS_ADDRCK(queue->first)) {
			return (queue->first->data);
		}
	}
	return (NULL);
}

/* EOF */