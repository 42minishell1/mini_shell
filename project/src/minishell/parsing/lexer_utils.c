/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:00:58 by jaehlee           #+#    #+#             */
/*   Updated: 2025/11/06 16:21:26 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 토큰 구조체와 내부 문자열을 해제한다 */
void	free_token(void *content)
{
	t_tok	*token;

	if (!content)
		return ;
	token = (t_tok *)content;
	if (token->value)
		free(token->value);
	free(token);
}

/* 공백 문자 여부를 판별한다 */
int	is_space(int c)
{
	return (c == ' ' || c == '\t' || c == '\n'
		|| c == '\r' || c == '\v' || c == '\f');
}

/* 한 글자 연산자인지 확인한다 */
int	is_op1(char c)
{
	return (c == '|' || c == '<' || c == '>');
}

/* 단어 토큰에 포함될 수 있는 문자인지 확인한다 */
int	is_word_char(char c)
{
	if (c == '\0')
		return (0);
	if (is_space(c))
		return (0);
	if (is_op1(c))
		return (0);
	return (1);
}

int	measure_word(char *line, int i)
{
	int		len;
	char	quote;

	len = 0;
	quote = 0;
	while (line[i + len])
	{
		if ((line[i + len] == '\'' || line[i + len] == '\"'))
		{
			if (quote == 0)
				quote = line[i + len];
			else if (quote == line[i + len])
				quote = 0;
			len++;
			continue ;
		}
		if (!quote && (is_space(line[i + len]) || is_op1(line[i + len])))
			break ;
		len++;
	}
	if (quote != 0)
		return (-1);
	return (len);
}
