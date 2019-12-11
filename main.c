#include <stdio.h>
#include <strings.h>

#include <ms_list_singly_linked.h>
#include <ms_list_doubly_linked.h>
#include <ms_list_circular_linked.h>
#include <ms_stack.h>
#include <ms_queue.h>
#include <ms_dict.h>
#include <ms_hash.h>
#include <ms_tree.h>
#include <ms_tree_rb.h>

# define SUCCESS 0
# define FAILURE 1

const char * str[] = {
	"Apricots",
	"Apple",
	"Banana",
	"Lime",
	"Mangoes",
	"Nectarines",
	"Passionfruit",
	"Peach",
	"Peer",
	"Raspberries",
	"Strawberries",
	NULL
};

size_t       size  = (sizeof(str) / sizeof(char *)) - 1;

static int f_print(void * data)
{
#ifdef DEBUG
	printf("%s\n", MS_CAST(char *, data));
#else
	MS_UNUSED(data);
#endif
	return (0);
}

int unit_list_singly(void)
{
	size_t     i;
	int        ret;
	char     * tmp;
	t_list_s * list;

	list = NULL;
	ret = list_s_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_s_push_front(&list, MS_CAST(void *, str[size - i - 1]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_s_nth_element(&list, i, 0x00));
		if (strcmp(str[i], tmp) != 0) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = list_s_fct(&list, &f_print);
	if (0 != ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	list_s_destroy(&list, NULL);
	ret = list_s_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_s_push_back(&list, MS_CAST(void *, str[i]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_s_nth_element(&list, size - i - 1, 0x00));
		if (0 != strcmp(str[size - i - 1], tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_s_last_element(&list, MS_ELEMENT_REMOVE));
		if (0 != strcmp(str[size - i - 1], tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = list_s_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	return (SUCCESS);
}

int unit_list_doubly(void)
{
	size_t     i;
	int        ret;
	char     * tmp;
	t_list_d * list;

	list = NULL;
	ret = list_d_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_d_push_front(&list, MS_CAST(void *, str[size - i - 1]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_d_nth_element(&list, i, 0x00));
		if (strcmp(str[i], tmp) != 0) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = list_d_fct(&list, &f_print);
	if (0 != ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	list_d_destroy(&list, NULL);
	ret = list_d_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_d_push_back(&list, MS_CAST(void *, str[i]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_d_nth_element(&list, size - i - 1, 0x00));
		if (strcmp(str[size - i - 1], tmp) != 0) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_d_last_element(&list, MS_ELEMENT_REMOVE));
		if (strcmp(str[size - i - 1], tmp) != 0) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = list_d_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	return (SUCCESS);
}

int unit_list_circular(void)
{
	size_t     i;
	int        ret;
	char     * tmp;
	t_list_c * list;

	list = NULL;
	ret = list_c_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_c_push(&list, MS_CAST(void *, str[i]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, list_c_nth_element(&list, i, 0x00));
		if (0 != strcmp(str[size - i - 1], tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = list_c_fct(&list, &f_print);
	if (0 != ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = size;
	while (i) {
		tmp = MS_CAST(char *, list_c_nth_element(&list, i, MS_ELEMENT_REMOVE));
		if (0 != strcmp(str[i - 1], tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[i - 1]);
			return (FAILURE);
		}
		--i;
	}
	ret = list_c_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	return (SUCCESS);
}

int unit_stack(void)
{
	size_t    i;
	int       ret;
	char    * tmp;
	t_stack * stack;

	stack = NULL;
	ret = stack_is_empty(stack);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = stack_init(&stack);
	if (1 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = stack_is_empty(stack);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = stack_push(stack, MS_CAST(void *, str[i]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, stack_pop(stack));
		if (strcmp(str[size - i - 1], tmp) != 0) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[size - i - 1]);
			return (FAILURE);
		}
		++i;
	}
	ret = stack_is_empty(stack);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	stack_destroy(stack, NULL);
	return (SUCCESS);
}

int unit_queue(void)
{
	size_t    i;
	int       ret;
	char    * tmp;
	t_queue * queue;

	queue = NULL;
	ret = queue_is_empty(queue);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = queue_init(&queue);
	if (1 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = queue_is_empty(queue);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = queue_enqueue(queue, MS_CAST(void *, str[i]), 0);
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	tmp = MS_CAST(char *, queue_peek(queue));
	if (0 != strcmp(str[0], tmp)) {
		printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[i]);
		return (FAILURE);
	}
	if (1 == queue_is_empty(queue)) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, queue_dequeue(queue));
		if (0 != strcmp(str[i], tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[i]);
			return (FAILURE);
		}
		++i;
	}
	ret = queue_is_empty(queue);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	queue_destroy(queue, NULL);
	return (SUCCESS);
}

static int f_compare(
	  void * data
	, unsigned char * key
	, size_t key_len
) {
	MS_UNUSED(key_len);
	return (strcmp(MS_CAST(char *, data), MS_CAST(char *, key)));
}

int unit_dictionary(void)
{
	size_t   i;
	int      ret;
	char   * tmp;
	t_dict * dict;

	dict = NULL;
	ret = dict_init(
		  &dict
		, size
		, &hash_fnv_onea
	);
	if (1 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = dict_insert(
			  dict
			, MS_CAST(void *, str[i])
			, 0
			, MS_CAST(unsigned char *, str[i])
			, strlen(str[i])
		);
		if (ret != 0) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	while (i < size) {
		tmp = MS_CAST(char *, dict_search(
			  dict
			, MS_CAST(unsigned char *, str[i])
			, strlen(str[i])
			, 0x00
			, &f_compare
		));
		if (MS_ADDRNULL(tmp)) {
			printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, str[i]);
			return (FAILURE);
		}
		++i;
	}
	tmp = MS_CAST(char *, dict_search(
		  dict
		, MS_CAST(unsigned char *, "Potato")
		, strlen("Potato")
		, MS_ELEMENT_REMOVE
		, &f_compare
	));
	if (MS_ADDRCK(tmp)) {
		printf("\n%s: %d => %s != %s - ", __FILE__, __LINE__, tmp, "Potato");
		return (FAILURE);
	}
	dict_destroy(dict, NULL);
	return (SUCCESS);
}

static int f_compare_2(
	  void * elem
	, void * data
) {
	return (strcmp(MS_CAST(char *, data), MS_CAST(char *, elem)));
}

static int f_print_2(void * data, void ** content)
{
	MS_UNUSED(content);
#ifdef DEBUG
	printf("%s\n", MS_CAST(char *, data));
#else
	MS_UNUSED(data);
#endif
	return (0);
}

int unit_tree(void)
{
	size_t   i;
	int      ret;
	t_tree * tree;

	tree = NULL;
	ret = tree_is_empty(tree);
	if (0 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = tree_insert(
			  &tree
			, MS_CAST(void *, str[i])
			, 0
			, &f_compare_2
		);
		if (0 != ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	ret = tree_in_order(
		  &tree
		, NULL
		, &f_print_2
	);
	if (0 != ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = tree_is_empty(tree);
	if (0 != ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	tree_destroy(&tree, NULL);
	ret = tree_is_empty(tree);
	if (0 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	return (SUCCESS);
}

int unit_tree_rb(void)
{
	size_t      i;
	int         ret;
	t_tree_rb * tree;

	tree = NULL;
	ret = tree_rb_is_empty(tree);
	if (0 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = tree_rb_insert(
			  &tree
			, MS_CAST(void *, str[i])
			, 0
			, &f_compare_2
		);
		if (0 != ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	ret = tree_rb_in_order(
		  &tree
		, NULL
		, &f_print_2
	);
	if (0 != ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	ret = tree_rb_is_empty(tree);
	if (0 != ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	tree_rb_destroy(&tree, NULL);
	ret = tree_rb_is_empty(tree);
	if (0 == ret) {
		printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	return (SUCCESS);
}

int main(void)
{
	printf("TEST: Singly-linked list: ");
	if (SUCCESS == unit_list_singly()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Doubly-linked list: ");
	if (SUCCESS == unit_list_doubly()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Circular Linked list: ");
	if (SUCCESS == unit_list_circular()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Stack: ");
	if (SUCCESS == unit_stack()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Queue: ");
	if (SUCCESS == unit_queue()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Dictionary: ");
	if (SUCCESS == unit_dictionary()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Tree: ");
	if (SUCCESS == unit_tree()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	printf("TEST: Red Black Tree: ");
	if (SUCCESS == unit_tree_rb()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	return (0);
}