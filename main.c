#include <stdio.h>
#include <strings.h>
#include <ms_struct.h>

// clang -Wall -Wextra -Werror -g -I includes main.c -o test

# define SUCCESS 0
# define FAILURE 1

const char	*str[] = {
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
size_t		size   = (sizeof(str) / sizeof(char *)) - 1;

static int	f_print(void *data) {
	printf("%s\n", MS_CAST(char *, data));
	return (0);
}

int			unit_list_singly(void)
{
	size_t   i;
	int      ret;
	char     *tmp;
	t_list_s *list;

	list = NULL;
	ret = list_s_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_s_push_front(&list, MS_CAST(void *, str[size - i - 1]));
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	i = 0;
	if (size != list_s_size(list)) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
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
	list_s_free(&list, NULL);
	ret = list_s_is_empty(list);
	if (0 == ret) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
	}
	i = 0;
	while (i < size) {
		ret = list_s_push_back(&list, MS_CAST(void *, str[i]));
		if (1 == ret) {
			printf("\n%s: %d => MALLOC - ", __FILE__, __LINE__);
			return (FAILURE);
		}
		++i;
	}
	if (size != list_s_size(list)) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
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
	if (size != list_s_size(list)) {
		printf("\n%s: %d - ", __FILE__, __LINE__);
		return (FAILURE);
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

int		main(int argc, char *argv[])
{
	(void)argc;
	(void)argv;

	printf("TEST: Singly-linked list: ");
	if (SUCCESS == unit_list_singly()) {
		printf("SUCESS\n");
	} else {
		printf("FAILURE\n");
	}
	return (0);
}