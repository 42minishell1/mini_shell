/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 20:06:01 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/16 20:06:01 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 입력 문자열을 토큰 리스트로 변환한다 */
t_list	*lexer(char *line)
{
	t_list	*tokens;
	int		i;
	int		len;

	i = 0;
	tokens = NULL;
	while (line[i])
	{
		if (is_space(line[i]))
		{
			i++;
			continue ;
		}
		len = tokenize_metachar(&tokens, line, i);
		if (len == 0)
			len = tokenize_word(&tokens, line, i);
		if (len == -1)
		{
			ft_lstclear(&tokens, &free_token);
			return (NULL);
		}
		i += len;
	}
	return (tokens);
}
