#ifndef MS_STACK_H
# define MS_STACK_H

# include <ms_struct.h>
# include <ms_content.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_stack;

/* Type opaque */
typedef struct s_stack t_stack;

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

/*! Stack init
 *
 * @brief Initialize an empty stack
 *
 * @param stack
 *     (input) stack to initialize
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int stack_init(t_stack ** stack);

/*! Stack free
 *
 * @brief Dealloc a stack
 *
 * @param stack
 *     (input) stack to free
 * @param f_free
 *     (input) function to free the data
 *             @param data
 *                 (input) data to free
 *             @result NaN
 *
 * @result NaN.
*/
void stack_free(
	  t_stack * stack
	, void (*f_free)(void * data)
);

/*------------------------------------- METHODS -------------------------------------*/

/*! Stack is empty
 *
 * @brief Check if the stack is empty
 *
 * @param stack
 *     (input) stack
 *
 * @result If successful, 1 is returned.
 *         Otherwise, a 0 is returned.
*/
int stack_is_empty(const t_stack * stack);

/*! Stack push
 *
 * @brief Push an element on top of the stack
 *
 * @param stack
 *     (input) stack
 * @param data
 *     (input) data to add to the stack
 * @param size
 *     (input) size of the content to allocate.
 *             If the size is 0, no copy occurs
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
int stack_push(
	  t_stack * stack
	, void * data
	, size_t size
);

/*! Stack pop
 *
 * @brief Pop the element on top of the stack
 *        and remove it from the stack
 *
 * @param stack
 *     (input) stack
 *
 * @result If successful, the data is returned.
 *         Otherwise, NULL is returned.
*/
void *stack_pop(t_stack * stack);

#endif /* !MS_STACK_H */

/* EOF */