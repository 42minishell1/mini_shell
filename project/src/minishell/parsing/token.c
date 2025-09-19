/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:13:09 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/16 21:13:09 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

static t_tok	*tok_new(t_toktype type, char *value)
{
	t_tok	*t;

	t = (t_tok *)malloc(sizeof(t_tok));
	if (!t)
		return (NULL);
	t->value = ft_linedup(value);
	if (!t->value)
	{
		free(t);
		return (NULL);
	}
	t->type = type;
	return (t);
}

static int	push_tok(t_list **list, t_toktype type, char *value)
{
	t_tok	*t;
	t_list	*node;

	t = tok_new(type, value);
	if (!t)
		return (-1);
	node = ft_lstnew(t);
	if (!node)
	{
		free(t->value);
		free(t);
		return (-1);
	}
	ft_lstadd_back(list, node);
	return (0);
}

static int	handle_redir(t_list **list, char *line, int i)
{
	if (line[i] == '>')
	{
		if (line[i + 1] == '>')
		{
			push_tok(list, T_DGT, ">>");
			return (2);
		}
		push_tok(list, T_GT, ">");
	}
	if (line[i] == '<')
	{
		if (line[i + 1] == '<')
		{
			push_tok(list, T_DLT, "<<");
			return (2);
		}
		push_tok(list, T_LT, "<");
		return (1);
	}
	return (0);
}

int	tokenize_metachar(t_list **list, char *line, int i)
{
	int	len;

	if (line[i] == '|')
	{
		push_tok(list, T_PIPE, "|");
		return (1);
	}
	else if (line[i] == '>' || line[i] == '<')
	{
		len = handle_redir(list, line, i);
		return (len);
	}
	return (0);
}

int	tokenize_word(t_list **tokens, char *line, int i)
{
	int		j;
	char	*word;

	j = 0;
	while (is_word_char(line[i + j]))
		j++;
	if (j == 0)
		return (0);
	word = ft_substr(line, i, j);
	if (!word)
		return (-1);
	push_tok(tokens, T_WORD, word);
	free(word);
	return (j);
}
