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

/* 노드에 지정된 입력 파일 또는 히어독 파일을 연다. */
static int	open_infile(t_pipe *node)
{
	int		fd;

	if (node->infile->type == F_IN)
		fd = open(node->infile->filename, O_RDONLY);
	else if (node->infile->type == F_HEREDOC)
		fd = open(node->infile->filename, O_RDONLY);
	else
		fd = -1;
	if (fd == -1)
		perror(node->infile->filename);
	return (fd);
}

/* 노드에 설정된 출력 파일을 모드에 맞게 열거나 생성한다. */
static int	open_outfile(t_pipe *node)
{
	int		fd;

	if (!node->outfile || !node->outfile->filename)
		return (STDOUT_FILENO);
	if (node->outfile->type == F_OUT_TRUNC)
		fd = open(node->outfile->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (node->outfile->type == F_OUT_APPEND)
		fd = open(node->outfile->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
		perror(node->outfile->filename);
	return (fd);
}

/* 파이프라인 노드의 표준 입출력 리다이렉션을 적용한다. */
int	open_redir(t_pipe *node)
{
	int	out_fd;

	node->fd = -1;
	out_fd = -1;
	if (node->infile)
	{
		node->fd = open_infile(node);
		if (node->fd == -1)
			return (-1);
		if (dup2(node->fd, STDIN_FILENO) == -1)
			return (close(node->fd), node->fd = -1, -1);
	}
	if (!node->outfile)
		return (0);
	out_fd = open_outfile(node);
	if (out_fd == -1)
		return (-1);
	if (dup2(out_fd, STDOUT_FILENO) == -1)
		return (close(out_fd), -1);
	close(out_fd);
	return (0);
}

/* 노드에 저장된 추가 입력 FD를 닫아 정리한다. */
void	close_redir(t_pipe *node)
{
	if (node->fd != -1)
	{
		close(node->fd);
		node->fd = -1;
	}
}
