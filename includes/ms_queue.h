#ifndef MS_QUEUE_H
# define MS_QUEUE_H

# include <ms_struct.h>
# include <ms_content.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_queue;

/* Type opaque */
typedef struct s_queue t_queue;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

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
int queue_init(t_queue ** queue);

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
void queue_free(
	  t_queue * queue
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

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
int queue_is_empty(const t_queue * queue);

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
int queue_enqueue(
	  t_queue * queue
	, void * data
	, size_t size
);

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
void *queue_dequeue(t_queue * queue);

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
void *queue_peek(t_queue * queue);

#endif /* !MS_QUEUE_H */

/* EOF */