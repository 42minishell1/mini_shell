/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:45:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/12/12 19:45:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 입력 리다이렉션 파일을 읽기 전용으로 연다.
static int	open_infile(const t_file *file)
{
	int	fd;

	fd = open(file->filename, O_RDONLY);
	if (fd == -1)
		perror(file->filename);
	return (fd);
}

// 출력 리다이렉션 파일을 모드에 맞게 생성/연다.
static int	open_outfile(const t_file *file)
{
	int	fd;

	if (file->type == F_OUT_TRUNC)
		fd = open(file->filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (file->type == F_OUT_APPEND)
		fd = open(file->filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	else
		fd = -1;
	if (fd == -1)
		perror(file->filename);
	return (fd);
}

// 표준입력을 지정 파일로 연결하고 이전 FD를 정리한다.
int	handle_in_redir(t_pipe *node, const t_file *file)
{
	int	fd;

	fd = open_infile(file);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDIN_FILENO) == -1)
		return (close(fd), -1);
	if (node->fd != -1)
		close(node->fd);
	node->fd = fd;
	return (0);
}

// 표준출력을 지정 파일로 연결한다.
int	handle_out_redir(const t_file *file)
{
	int	fd;

	fd = open_outfile(file);
	if (fd == -1)
		return (-1);
	if (dup2(fd, STDOUT_FILENO) == -1)
		return (close(fd), -1);
	close(fd);
	return (0);
}
