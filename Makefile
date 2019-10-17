CC        = clang
RM        = rm -rf
NAME      = libstruct.a
LIB       = -L. -lstruct
CFLAGS    = -Wall -Wextra -Werror
DEBUG     = -g -DDEBUG

TEST      = test

INCLUDES  = -I includes/

CONTENT   = ms_content.c
DICT      = ms_dict.c ms_hash.c
LIST      = ms_list_singly_linked.c ms_list_circular_linked.c ms_list_doubly_linked.c
QUEUE     = ms_queue.c
STACK     = ms_stack.c
TREE      = ms_tree.c ms_tree_rb.c

FUNCTIONS = $(CONTENT) $(DICT) $(LIST) $(QUEUE) $(STACK) $(TREE)
FILES     = $(addprefix srcs/, $(FUNCTIONS))
OBJECTS   = $(FILES:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

test: $(NAME)
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDES) main.c -o $(TEST) $(LIB)

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TEST)*

re: fclean all