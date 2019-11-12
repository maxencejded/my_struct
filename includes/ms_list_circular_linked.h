#ifndef MS_LIST_CIRCULAR_H
# define MS_LIST_CIRCULAR_H

# include <ms_struct.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_list_c;

/* Type opaque */
typedef struct s_list_c t_list_c;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Circular Linked List node init
 *
 * @brief Create a node for the circular linked list
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
t_list_c * list_c_node(
	  void * data
	, size_t size
);

/*! Circular Linked List free
 *
 * @brief Dealloc an circular linked list
 *
 * @param list
 *     (input) circular linked list to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
void list_c_free(
	  t_list_c ** list
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

/*! Circular Linked is empty
 *
 * @brief Check if the circular linked list is empty
 *
 * @param list
 *     (input) circular linked list
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
int list_c_is_empty(const t_list_c * list);

/*! Circular Linked List function
 *
 * @brief Apply a function to each nodes of circular linked list
 *
 * @param list
 *     (input) circular linked list
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
int list_c_fct(
	  t_list_c ** list
	, int (*f_fct)(void * data)
);

/*! Circular Linked List push
 *
 * @brief Push an element on the circular linked list
 *
 * @param list
 *     (input) address of the circular linked list
 * @param data
 *     (input) data to add to the list
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int list_c_push(
	  t_list_c ** list
	, void * data
	, size_t size
);

/*! Circular Linked List first element
 *
 * @brief Return the first element of circular linked list
 *
 * @param list
 *     (input) circular linked list
 * @param flag
 *     (input) if set to MS_ELEMENT_REMOVE remove it when returned
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_c_element(
	  t_list_c ** list
	, int flag
);

/*! Circular Linked List n-th element
 *
 * @brief Return the n-th element of circular linked list
 *
 * @param list
 *     (input) circular linked list
 * @param n
 *     (input) n-th element to return
 * @param flag
 *     (input) if bit set to MS_ELEMENT_REMOVE remove it while returned
 *
 * @note The n-th element can be the first element of the list
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void * list_c_nth_element(
	  t_list_c ** list
	, size_t n
	, int flag
);

#endif /* !MS_LIST_CIRCULAR_H */

/* EOF */