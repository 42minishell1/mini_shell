/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:45:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/12/12 19:45:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 리다이렉션 정보를 담는 새 파일 구조체를 생성한다.
t_file	*file_new(const char *filename, t_ftype type, int quoted)
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

// 파이프 노드의 리다이렉션 리스트 끝에 파일 노드를 추가한다.
static int	append_redir(t_pipe *pipe, t_file *file)
{
	t_list	*node;

	node = ft_lstnew(file);
	if (!node)
	{
		free(file->filename);
		free(file);
		errno = ENOMEM;
		return (PARSE_ALLOC_ERROR);
	}
	ft_lstadd_back(&pipe->redirs, node);
	return (PARSE_OK);
}

// 특정 방향의 리다이렉션 슬롯을 지정 파일로 채운다.
int	set_file(t_pipe *pipe, t_file **slot, t_file *file)
{
	if (!pipe || !slot || !file || !file->filename)
		return (PARSE_SYNTAX_ERROR);
	if (append_redir(pipe, file) == PARSE_ALLOC_ERROR)
		return (PARSE_ALLOC_ERROR);
	*slot = file;
	return (PARSE_OK);
}
