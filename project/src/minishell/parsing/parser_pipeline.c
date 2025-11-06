/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_pipeline.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:34:11 by jaehlee           #+#    #+#             */
/*   Updated: 2025/10/25 16:10:29 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 파이프 노드가 실행할 내용이 없는지 확인한다 */
static int	pipe_is_empty(t_pipe *pipe)
{
	if (!pipe)
		return (1);
	if (pipe->cmd)
		return (0);
	if (pipe->infile || pipe->outfile || pipe->herelist)
		return (0);
	return (1);
}

/* 토큰 커서 위치에서 파이프 노드 하나를 구성한다 */
static int	process_pipeline_node(t_list **cursor, t_pipe **head, t_pipe **tail)
{
	t_pipe	*node;
	int		status;

	node = pipe_new();
	if (!node)
		return (PARSE_ALLOC_ERROR);
	if (!*head)
		*head = node;
	else
		(*tail)->next = node;
	*tail = node;
	status = parse_segment(node, cursor);
	if (status != PARSE_OK)
		return (status);
	if (pipe_is_empty(node))
		return (PARSE_SYNTAX_ERROR);
	if (*cursor && ((t_tok *)(*cursor)->content)->type == T_PIPE)
	{
		*cursor = (*cursor)->next;
		if (!*cursor)
			return (PARSE_SYNTAX_ERROR);
	}
	return (PARSE_OK);
}

/* 토큰 리스트 전체를 파이프라인 연결 리스트로 변환한다 */
int	build_pipeline(t_list *tokens, t_pipe **out)
{
	t_pipe	*head;
	t_pipe	*tail;
	int		status;

	head = NULL;
	tail = NULL;
	while (tokens)
	{
		status = process_pipeline_node(&tokens, &head, &tail);
		if (status != PARSE_OK)
		{
			free_pipeline(head);
			return (status);
		}
	}
	*out = head;
	return (PARSE_OK);
}
