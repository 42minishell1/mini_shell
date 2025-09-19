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
	t->value = ft_strdup(value);
	if (!t->value)
	{
		free(t);
		return (NULL);
	}
	t->type = type;
	return (t);
}

int	push_tok(t_list **list, t_toktype type, char *value)
{
	t_tok	*t;
	t_list	*node;

	t = tok_new(type, value);
	if (!t)
		return (-1);
	node = ft_lstnew(t);
	if (!node)
		return (-1);
	ft_lstadd_back(list, node);
	return (0);
}

char	*ft_strtok(char *str)
{
	int		i;
	int		start;
	int		end;

	i = 0;
	start = 0;
	while (str[i] != '\0')
	{
		
	}
}
