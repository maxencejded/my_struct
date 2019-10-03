#include <ms_stack.h>

/*----------------------------------- STRUCTURES ------------------------------------*/

struct s_stack
{
	t_content * content;
};

/*-------------------------------- CONSTRUCTOR/DESTR --------------------------------*/

int stack_init(t_stack ** stack)
{
	if (MS_ADDRCK(stack)) {
		*stack = MS_CAST(t_stack *, MS_ALLOC(sizeof(t_stack)));
		if (MS_ADDRCK(*stack)) {
			MS_MEMSET(*stack, 0, sizeof(t_stack));
			return (0);
		}
	}
	return (1);
}

void stack_free(
	  t_stack * stack
	, void (*f_free)(void * data)
) {
	t_content * content;

	if (MS_ADDRCK(stack)) {
		while (MS_ADDRCK(stack->content))
		{
			content = stack->content;
			stack->content = stack->content->next;
			if (MS_ADDRCK(f_free)) {
				f_free(content->data);
			}
			MS_DEALLOC(content);
		}		
		MS_DEALLOC(stack);
	}
}

/*------------------------------------- METHODS -------------------------------------*/

int stack_is_empty(const t_stack * stack)
{
	if (MS_ADDRCK(stack)) {
		if (MS_ADDRCK(stack->content)) {
			return (0);
		}
	}
	return (1);
}

int stack_push(
	  t_stack * stack
	, void * data
	, size_t size
) {
	t_content * content;

	if (
		   MS_ADDRCK(stack)
		&& MS_ADDRCK(data)
	) {
		content = content_init(data, size);
		if (MS_ADDRCK(content)) {
			content->next = stack->content;
			stack->content = content;
			return (0);
		}
	}
	return (1);
}

void *stack_pop(t_stack * stack)
{
	void      * data;
	t_content * content;

	if (MS_ADDRCK(stack)) {
		content = stack->content;
		if (MS_ADDRCK(content)) {
			stack->content = content->next;
			data = content->data;
			MS_DEALLOC(content);
			return (data);
		}
	}
	return (NULL);
}

/* EOF */