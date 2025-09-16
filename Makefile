NAME = minishell

DIRECTORY = ./project

SOURCE = $(DIRECTORY)/src

LIBFT = $(SOURCE)/libft
MINISHELL = $(SOURCE)/minishell

LIBRARY = $(DIRECTORY)/library

MINISHELL_A = $(LIBRARY)/minishell.a
LIBFT_A = $(LIBRARY)/libft.a

CC = cc -Wall -Wextra -Werror -g

all: $(NAME)

$(NAME): $(MINISHELL_A) $(LIBFT_A)
	@$(CC) $^ -o $@
	
$(MINISHELL_A): $(MINISHELL)
	@$(MAKE) -C $(MINISHELL) -s

$(LIBFT_A): $(LIBFT)
	@$(MAKE) -C $(LIBFT) -s

clean:
	@$(MAKE) -C $(MINISHELL) fclean -s
	@$(MAKE) -C $(LIBFT) fclean -s
	@rm -rf .depend
	
fclean: clean
	@rm -rf $(NAME)
	
re: fclean all

.PHONY: all clean fclean re bonus
