/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 11:12:45 by jaehlee           #+#    #+#             */
/*   Updated: 2025/11/06 15:50:23 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 한 줄에 공백 이외 문자가 있는지 검사한다 */
static int	has_nonspace(const char *line)
{
	size_t	i;

	if (!line)
		return (0);
	i = 0;
	while (line[i])
	{
		if (!is_space((unsigned char)line[i]))
			return (1);
		i++;
	}
	return (0);
}

/* 한 줄을 파싱해 파이프라인 구조체를 생성한다 */
int	parse_line(char *line, t_pipe **pipeline)
{
	t_list	*tokens;
	int		status;

	if (!pipeline)
		return (PARSE_SYNTAX_ERROR);
	*pipeline = NULL;
	errno = 0;
	tokens = lexer(line);
	if (!tokens)
	{
		if (!has_nonspace(line))
			return (PARSE_OK);
		if (errno == ENOMEM)
			return (PARSE_ALLOC_ERROR);
		return (PARSE_SYNTAX_ERROR);
	}
	status = build_pipeline(tokens, pipeline);
	ft_lstclear(&tokens, &free_token);
	return (status);
}
