CC = cc -c -Wall -Wextra -Werror -g
NAME = minishell.a

INC = -I ../../includes
LIB = ../../library

SRCS = \
main.c prompt.c\


OBJS = $(SRCS:.c=.o)

all: $(NAME)

%.o: %.c
	@$(CC) $^ -o $@ $(INC)

$(NAME): $(OBJS)
	@mkdir -p ../../library
	@ar -rcs $(LIB)/$(NAME) $^

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(LIB)/$(NAME)

re: fclean all

.PHONY: all clean fclean re
