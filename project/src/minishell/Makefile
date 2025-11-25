CC = cc -c -Wall -Wextra -Werror -g
NAME = minishell.a

INC = -I ../../includes
LIB = ../../library

SRCS = \
	main.c \
	prompt.c \
	execution/exec_external.c \
	execution/exec_pipeline.c \
	execution/exec_pipeline_child.c \
	execution/exec_wait.c \
	execution/heredoc.c \
	execution/heredoc_utils.c \
	execution/heredoc_writer.c \
	execution/redir.c \
	execution/builtin.c \
	oooo/echo.c \
	oooo/cd.c \
	oooo/pwd.c \
	oooo/export.c \
	oooo/env.c \
	oooo/exit.c \
	utils/shell_state.c \
	parsing/lexer.c \
	parsing/lexer_tokens.c \
	parsing/lexer_utils.c \
	parsing/parser.c \
	parsing/parser_nodes.c \
	parsing/parser_segment.c \
	parsing/parser_pipeline.c \
	parsing/parser_args.c \
	parsing/parser_cleanup.c

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
