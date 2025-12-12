CC = cc -c -Wall -Wextra -Werror -g
NAME = minishell.a

INC = -I ../../includes
LIB = ../../library

SRCS = \
	core/main.c \
	core/prompt.c \
	core/shell_state.c \
	core/signals.c \
	execution/external/exec_external.c \
	execution/pipeline/exec_pipeline.c \
	execution/pipeline/exec_pipeline_child.c \
	execution/pipeline/exec_wait.c \
	execution/pipeline/exec_utils.c \
	execution/redirects/heredoc.c \
	execution/redirects/heredoc_utils.c \
	execution/redirects/heredoc_writer.c \
	execution/redirects/redir.c \
	execution/redirects/redir_utils.c \
	execution/env/env_utils.c \
	execution/builtins/builtin.c \
	execution/builtins/echo.c \
	execution/builtins/cd.c \
	execution/builtins/pwd.c \
	execution/builtins/export.c \
	execution/builtins/env.c \
	execution/builtins/exit.c \
	execution/builtins/unset.c \
	parsing/lexer/lexer.c \
	parsing/lexer/lexer_tokens.c \
	parsing/lexer/lexer_utils.c \
	parsing/parser/parser.c \
	parsing/parser/parser_nodes.c \
	parsing/parser/parser_segment.c \
	parsing/parser/parser_segment_utils.c \
	parsing/parser/parser_pipeline.c \
	parsing/parser/parser_redir.c \
	parsing/parser/parser_args.c \
	parsing/expansion/expansion_shared.c \
	parsing/expansion/expansion_buffer.c \
	parsing/expansion/expansion_word.c \
	parsing/expansion/expansion_simple.c \
	parsing/parser/parser_cleanup.c

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
