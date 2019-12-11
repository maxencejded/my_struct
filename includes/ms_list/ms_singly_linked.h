#ifndef MS_SINGLY_LINKED_H
# define MS_SINGLY_LINKED_H

# include <ms_struct.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_list_s;

/* Type opaque */
typedef struct s_list_s t_list_s;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Singly-linked List node init
 *
 * @brief Create a node for the singly-linked list
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
t_list_s * list_s_node(
	  void * data
	, size_t size
);

/*! Singly-linked List destroy
 *
 * @brief Dealloc an singly-linked list
 *
 * @param list
 *     (input) singly-linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
void list_s_destroy(
	  t_list_s ** list
	, void (*f_free)(void *data)
);

/*------------------------------------- METHODS -------------------------------------*/

/*! Singly-linked is empty
 *
 * @brief Check if the singly-linked list is empty
 *
 * @param list
 *     (input) singly-linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
int list_s_is_empty(const t_list_s * list);

/*! Singly-linked List function
 *
 * @brief Apply a function to each nodes of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
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
int list_s_fct(
	  t_list_s ** list
	, int (*f_fct)(void * data)
);

/*! Singly-linked List push front
 *
 * @brief Push an element on top of singly-linked list
 *
 * @param list
 *     (input) address of the singly-linked list
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int list_s_push_front(
	  t_list_s ** list
	, void * data
	, size_t size
);

/*! Singly-linked List push back
 *
 * @brief Push an element at the bottom of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int list_s_push_back(
	  t_list_s ** list
	, void * data
	, size_t size
);

/*! Singly-linked List first element
 *
 * @brief Return the first element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_s_first_element(
	  t_list_s ** list
	, int flag
);

/*! Singly-linked List last element
 *
 * @brief Return the last element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_s_last_element(
	  t_list_s ** list
	, int flag
);

/*! Singly-linked List n-th element
 *
 * @brief Return the n-th element of singly-linked list
 *
 * @param list
 *     (input) singly-linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void *list_s_nth_element(
	  t_list_s ** list
	, size_t n
	, int flag
);

#endif /* !MS_SINGLY_LINKED_H */

/* EOF */