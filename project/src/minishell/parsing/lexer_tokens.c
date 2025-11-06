/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 21:13:09 by jaehlee           #+#    #+#             */
/*   Updated: 2025/11/06 16:00:37 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 새 토큰 구조체를 할당하고 초기화한다 */
static t_tok	*tok_new(t_toktype type, const char *value)
{
	t_tok	*t;

	t = (t_tok *)malloc(sizeof(t_tok));
	if (!t)
	{
		errno = ENOMEM;
		return (NULL);
	}
	t->value = ft_strdup(value);
	if (!t->value)
	{
		free(t);
		errno = ENOMEM;
		return (NULL);
	}
	t->type = type;
	t->next = NULL;
	return (t);
}

/* 토큰 리스트 끝에 새 토큰을 추가한다 */
int	push_tok(t_list **list, t_toktype type, char *value)
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
		errno = ENOMEM;
		return (-1);
	}
	ft_lstadd_back(list, node);
	return (0);
}

/* 리다이렉션 연속 문자를 해석해 토큰으로 만든다 */
static int	handle_redir(t_list **list, const char *line)
{
	if (line[0] == '>' && line[1] == '>')
	{
		if (push_tok(list, T_DGT, ">>") == -1)
			return (-1);
		return (2);
	}
	if (line[0] == '>')
	{
		if (push_tok(list, T_GT, ">") == -1)
			return (-1);
		return (1);
	}
	if (line[0] == '<' && line[1] == '<')
	{
		if (push_tok(list, T_DLT, "<<") == -1)
			return (-1);
		return (2);
	}
	if (line[0] == '<')
	{
		if (push_tok(list, T_LT, "<") == -1)
			return (-1);
		return (1);
	}
	return (0);
}

/* 현재 위치에서 파이프/리다이렉션 토큰을 추출한다 */
int	tokenize_metachar(t_list **list, char *line, int i)
{
	int	len;

	if (line[i] == '|')
	{
		if (push_tok(list, T_PIPE, "|") == -1)
			return (-1);
		return (1);
	}
	if (line[i] == '>' || line[i] == '<')
	{
		len = handle_redir(list, line + i);
		if (len == -1)
			return (-1);
		return (len);
	}
	return (0);
}

/* 현재 위치에서 일반 단어 토큰을 추출한다 */
int	tokenize_word(t_list **tokens, char *line, int i)
{
	int		j;
	char	*word;

	j = 0;
	while (line[i + j] && is_word_char(line[i + j]))
		j++;
	if (j == 0)
		return (0);
	word = ft_substr(line, i, j);
	if (!word)
	{
		errno = ENOMEM;
		return (-1);
	}
	if (push_tok(tokens, T_WORD, word) == -1)
	{
		free(word);
		return (-1);
	}
	free(word);
	return (j);
}
