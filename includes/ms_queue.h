#ifndef MS_QUEUE_H
# define MS_QUEUE_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_queue
{
	t_content			*first;
	t_content			*last;
}						t_queue;

/*! Queue init
 *
 * @brief Initialize an emptyr queue
 *
 * @param queue
 *     (input) queue to initialize
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			queue_init(t_queue **queue)
{
	if (MS_ADDRK(queue)) {
		*queue = MS_CAST(t_queue *, MS_ALLOC(sizeof(t_queue)));
		if (MS_ADDRK(*queue)) {
			MS_MEMSET(*queue, 0, sizeof(t_queue));
			return (0);
		}
	}
	return (1);
}

/*! Queue free
 *
 * @brief Dealloc a queue
 *
 * @param queue
 *     (input) queue to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN
*/
static inline
void		queue_free(
	  t_queue *queue
	, void (*f_free)(void *data)
) {
	t_content	*content;

	if (MS_ADDRK(queue)) {
		while (MS_ADDRK(queue->first))
		{
			content = queue->first;
			queue->first = queue->first->next;
			if (MS_ADDRK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}		
		MS_DEALLOC(queue);
	}
}

/*! Queue is empty
 *
 * @brief Check if the queue is empty
 *
 * @param queue
 *     (input) queue
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
static inline
int			queue_is_empty(const t_queue *queue)
{
	if (MS_ADDRK(queue)) {
		if (MS_ADDRK(queue->first)) {
			return (0);
		}
	}
	return (1);
}

/*! Queue enqueue
 *
 * @brief Insert an element at the end of the queue
 *
 * @param queue
 *     (input) queue
 * @param data
 *     (input) data to add to the queue
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			queue_enqueue(
	  t_queue *queue
	, void *data
	, size_t size
) {
	t_content	*content;

	if (
		   MS_ADDRK(queue)
		&& MS_ADDRK(data)
	) {
		content = content_init(data, size);
		if (MS_ADDRK(content)) {
			if (MS_ADDRK(queue->last)) {
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

/*! Queue dequeue
 *
 * @brief Return the first element of the queue
 *        and remove it from the queue
 *
 * @param queue
 *     (input) queue
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void		*queue_dequeue(t_queue *queue)
{
	void		*data;
	t_content	*content;

	if (MS_ADDRK(queue)) {
		content = queue->first;
		if (MS_ADDRK(content)) {
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

/*! Queue peek
 *
 * @brief Return the first element of the queue
 *
 * @param queue
 *     (input) queue
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void		*queue_peek(t_queue *queue)
{
	if (MS_ADDRK(queue)) {
		if (MS_ADDRK(queue->first)) {
			return (queue->first->data);
		}
	}
	return (NULL);
}

#endif