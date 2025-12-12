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

static int	finalize_heredoc_file(t_file *redir, const char *path)
{
	free(redir->filename);
	redir->filename = ft_strdup(path);
	if (!redir->filename)
		return (-1);
	redir->type = F_IN;
	return (0);
}

int	process_single_heredoc(t_shell *shell, t_file *redir, t_heredoc *hd)
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
	if (finalize_heredoc_file(redir, tmp_path) == -1)
	{
		unlink(tmp_path);
		free(tmp_path);
		return (-1);
	}
	free(tmp_path);
	return (0);
}
