/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 16:49:27 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 16:49:27 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	handle_in_redir(t_pipe *node, const t_file *file);
int	handle_out_redir(const t_file *file);

// 리다이렉션 타입에 따라 적절한 처리 함수를 호출한다.
static int	apply_redir(t_pipe *node, t_file *file)
{
	if (!file || !file->filename)
		return (0);
	if (file->type == F_IN || file->type == F_HEREDOC)
		return (handle_in_redir(node, file));
	if (file->type == F_OUT_TRUNC || file->type == F_OUT_APPEND)
		return (handle_out_redir(file));
	return (0);
}

// 리다이렉션 리스트를 순회하며 파일 디스크립터를 연다.
int	open_redir(t_pipe *node)
{
	t_list	*cur;
	t_file	*file;

	node->fd = -1;
	cur = node->redirs;
	while (cur)
	{
		file = (t_file *)cur->content;
		if (apply_redir(node, file) == -1)
			return (close_redir(node), -1);
		cur = cur->next;
	}
	return (0);
}

// 열려 있는 리다이렉션 FD를 정리한다.
void	close_redir(t_pipe *node)
{
	if (node->fd != -1)
	{
		close(node->fd);
		node->fd = -1;
	}
}
