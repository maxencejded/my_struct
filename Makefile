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
LISTS	  = ms_singly_linked.c \
			ms_circular_linked.c \
			ms_doubly_linked.c
LIST      = $(addprefix ms_list/, $(LISTS))
QUEUE     = ms_queue.c
STACK     = ms_stack.c
TREES     = ms_binary.c \
			ms_red_black.c
TREE      = $(addprefix ms_tree/, $(TREES))

FUNCTIONS = $(CONTENT) $(DICT) $(LIST) $(QUEUE) $(STACK) $(TREE)
FILES     = $(addprefix sources/, $(FUNCTIONS))
OBJECTS   = $(FILES:.c=.o)

.PHONY: all $(NAME) clean fclean re

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJECTS)
	@ar rc $(NAME) $(OBJECTS)
	@ranlib $(NAME)

test: $(NAME)
	$(CC) $(CFLAGS) $(DEBUG) $(INCLUDES) misc/main.c -o $(TEST) $(LIB)

clean:
	@$(RM) $(OBJECTS)

fclean: clean
	@$(RM) $(NAME)
	@$(RM) $(TEST)*

re: fclean all