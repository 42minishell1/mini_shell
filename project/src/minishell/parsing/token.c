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

static t_tok	*tok_new(t_toktype type, char *lex, int quoted)
{
	t_tok	*t;

	t = (t_tok *)malloc(sizeof(t_tok));
	if (!t)
		return (NULL);
	t->type = type;
	t->lex = lex;
	t->quoted = quoted;
	return (t);
}

int	push_tok(t_list **list, t_toktype type, char *lex, int quoted)
{
	t_tok	*t;
	t_list	*node;

	t = tok_new(type, lex, quoted);
	if (!t)
		return (-1);
	node = ft_lstnew(t);
	if (!node)
		return (-1);
	ft_lstadd_back(list, node);
	return (0);
}
