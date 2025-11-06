/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_nodes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:34:11 by jaehlee           #+#    #+#             */
/*   Updated: 2025/11/06 15:43:22 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 리다이렉션 정보를 담을 파일 구조체를 생성한다 */
static t_file	*file_new(const char *filename, t_ftype type, int quoted)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
	{
		errno = ENOMEM;
		return (NULL);
	}
	file->filename = ft_strdup(filename);
	if (!file->filename)
	{
		free(file);
		errno = ENOMEM;
		return (NULL);
	}
	file->type = type;
	file->quoted = quoted;
	return (file);
}

/* 빈 파이프 노드를 생성하고 기본값을 세팅한다 */
t_pipe	*pipe_new(void)
{
	t_pipe	*node;

	node = (t_pipe *)ft_calloc(1, sizeof(t_pipe));
	if (!node)
	{
		errno = ENOMEM;
		return (NULL);
	}
	node->fd = -1;
	return (node);
}

/* 파이프 노드에 리다이렉션 파일 정보를 설정한다 */
int	set_file(t_file **slot, const char *filename, t_ftype type, int quoted)
{
	t_file	*file;

	if (!slot || !filename)
		return (PARSE_SYNTAX_ERROR);
	file = file_new(filename, type, quoted);
	if (!file)
		return (PARSE_ALLOC_ERROR);
	if (*slot)
	{
		free((*slot)->filename);
		free(*slot);
	}
	*slot = file;
	return (PARSE_OK);
}

/* heredoc 리스트의 끝에 노드를 이어 붙인다 */
static void	add_heredoc_tail(t_pipe *pipe, t_heredoc *node)
{
	t_heredoc	*tail;

	if (!pipe->herelist)
	{
		pipe->herelist = node;
		return ;
	}
	tail = pipe->herelist;
	while (tail->next)
		tail = tail->next;
	tail->next = node;
}

/* heredoc 노드를 생성해 파이프 노드에 추가한다 */
int	append_heredoc_node(t_pipe *pipe, const char *delimiter, int quoted)
{
	t_heredoc	*node;

	node = (t_heredoc *)malloc(sizeof(t_heredoc));
	if (!node)
	{
		errno = ENOMEM;
		return (PARSE_ALLOC_ERROR);
	}
	node->delim = ft_strdup(delimiter);
	if (!node->delim)
	{
		free(node);
		errno = ENOMEM;
		return (PARSE_ALLOC_ERROR);
	}
	node->quoted = quoted;
	node->next = NULL;
	add_heredoc_tail(pipe, node);
	return (PARSE_OK);
}
