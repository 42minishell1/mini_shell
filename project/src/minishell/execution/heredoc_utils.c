/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:40:59 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 15:40:59 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 히어독 입력을 위한 고유 임시 파일을 만들고 FD를 반환한다. */
static int	open_temp(char **path_out)
{
	char	*path;
	int		fd;

	path = ft_strdup(HEREDOC_TEMPLATE);
	if (!path)
		return (-1);
	fd = mkstemp(path);
	if (fd == -1)
	{
		perror("minishell: heredoc");
		free(path);
		return (-1);
	}
	*path_out = path;
	return (fd);
}

/* 생성된 히어독 경로로 infile 정보를 교체한다. */
static int	finalize_heredoc(t_pipe *pipe, const char *path)
{
	free(pipe->infile->filename);
	pipe->infile->filename = ft_strdup(path);
	if (!pipe->infile->filename)
		return (-1);
	pipe->infile->type = F_IN;
	return (0);
}

/* 히어독 하나를 생성해 내용 작성 후 노드에 할당한다. */
int	process_single_heredoc(t_shell *shell, t_pipe *pipe, t_heredoc *hd)
{
	char	*tmp_path;
	int		fd;

	(void)shell;
	fd = open_temp(&tmp_path);
	if (fd == -1)
		return (-1);
	if (write_heredoc_body(shell, hd->delim, hd->quoted, fd) == -1)
	{
		close(fd);
		unlink(tmp_path);
		free(tmp_path);
		return (-1);
	}
	close(fd);
	if (finalize_heredoc(pipe, tmp_path) == -1)
	{
		unlink(tmp_path);
		free(tmp_path);
		return (-1);
	}
	free(tmp_path);
	return (0);
}
