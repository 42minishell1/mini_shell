/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:00:58 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/16 22:00:58 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_token_content(void *content)
{
	t_tok	*token;

	if (!content)
		return ;
	token = (t_tok *)content;
	if (token->value)
		free(token->value);
	free(token);
}

int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		||c == '\r' || c == '\v' || c == '\f');
}

int	is_op1(char *c)
{
	return (c == "|" || c == "<" || c == ">" || c == "<<" || c == ">>");
}

int	is_word_char(char c)
{
	return (c == '\0' || c == ' ' || c == '\t'
		|| c == '|' || c == '<' || c == '>');
}
