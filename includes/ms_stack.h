#ifndef MS_STACK_H
# define MS_STACK_H

# ifndef MS_STRUCT_H
# include <ms_struct.h>
# endif

typedef struct			s_stack
{
	t_content			*content;
}						t_stack;

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
static inline
int			stack_init(t_stack **stack)
{
	if (MS_ADDRK(stack)) {
		*stack = MS_CAST(t_stack *, MS_ALLOC(sizeof(t_stack)));
		if (MS_ADDRK(*stack)) {
			MS_MEMSET(*stack, 0, sizeof(t_stack));
			return (0);
		}
	}
	return (1);
}

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
static inline
void		stack_free(
	  t_stack *stack
	, void (*f_free)(void *data)
) {
	t_content	*content;

	if (MS_ADDRK(stack)) {
		while (MS_ADDRK(stack->content))
		{
			content = stack->content;
			stack->content = stack->content->next;
			if (MS_ADDRK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}		
		MS_DEALLOC(stack);
	}
}

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
static inline
int			stack_is_empty(t_stack *stack)
{
	if (MS_ADDRK(stack)) {
		if (MS_ADDRK(stack->content)) {
			return (0);
		}
	}
	return (1);
}

/*! Stack push
 *
 * @brief Push an element on top of the stack
 *
 * @param stack
 *     (input) stack
 * @param data
 *     (input) data to add to the stack
 *
 * @result If successful, 0 is returned.
 *         Otherwise, a 1 is returned.
*/
static inline
int			stack_push(
	  t_stack *stack
	, void *data
) {
	t_content	*content;

	if (
		   MS_ADDRK(stack)
		&& MS_ADDRK(data)
	) {
		content = content_init(data);
		if (MS_ADDRK(content)) {
			content->next = stack->content;
			stack->content = content;
			return (0);
		}
	}
	return (1);
}

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
void		*stack_pop(t_stack *stack)
{
	void		*data;
	t_content	*content;

	if (MS_ADDRK(stack)) {
		content = stack->content;
		if (MS_ADDRK(content)) {
			stack->content = content->next;
			data = content->data;
			MS_DEALLOC(content);
			return (data);
		}
	}
	return (NULL);
}

#endif