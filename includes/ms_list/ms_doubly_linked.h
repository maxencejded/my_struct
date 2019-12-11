#ifndef MS_DOUBLY_LINKED_H
# define MS_DOUBLY_LINKED_H

# include <ms_struct.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_list_d;

/* Type opaque */
typedef struct s_list_d t_list_d;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Doubly-linked List node init
 *
 * @brief Create a node for the doubly-linked list
 *
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, the node is returned.
 *         Otherwise, NULL is returned.
*/
t_list_d * list_d_node(
	  void * data
	, size_t size
);

/*! Doubly-linked List destroy
 *
 * @brief Dealloc an doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
void list_d_destroy(
	  t_list_d ** list
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

/*! Doubly-linked List is empty
 *
 * @brief Check if the doubly-linked list is empty
 *
 * @param list
 *     (input) doubly-linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
int list_d_is_empty(const t_list_d * list);

/*! Doubly-linked List function
 *
 * @brief Apply a function to each nodes of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param f_fct
 *     (input) function to apply on the data
 *             @param data
 *                 (input) data
 *             @result If successful, 0 is returned.
 *                     Otherwise, a number is returned.
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a number is returned.
*/
int list_d_fct(
	  t_list_d ** list
	, int (*f_fct)(void * data)
);

/*! Doubly-linked List push front
 *
 * @brief Push an element on top of doubly-linked list
 *
 * @param list
 *     (input) address of the doubly-linked list
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int list_d_push_front(
	  t_list_d ** list
	, void * data
	, size_t size
);

/*! Doubly-linked List push back
 *
 * @brief Push an element at the bottom of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int list_d_push_back(
	  t_list_d ** list
	, void * data
	, size_t size
);

/*! Doubly-linked List first element
 *
 * @brief Return the first element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_d_first_element(
	  t_list_d ** list
	, int flag
);

/*! Doubly-linked List last element
 *
 * @brief Return the last element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_d_last_element(
	  t_list_d ** list
	, int flag
);

/*! Doubly-linked List n-th element
 *
 * @brief Return the n-th element of doubly-linked list
 *
 * @param list
 *     (input) doubly-linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void *list_d_nth_element(
	  t_list_d ** list
	, size_t n
	, int flag
);

#endif /* !MS_DOUBLY_LINKED_H */

/* EOF */