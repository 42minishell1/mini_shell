/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:29:21 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 15:29:21 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	prepare_heredocs(t_shell *shell, t_pipe *pipeline)
{
	t_pipe		*node;
	t_heredoc	*hd;
	t_list		*redir;

	node = pipeline;
	while (node)
	{
		hd = node->herelist;
		redir = node->redirs;
		while (hd)
		{
			while (redir && ((t_file *)redir->content)->type != F_HEREDOC)
				redir = redir->next;
			if (!redir)
				return (-1);
			if (process_single_heredoc(shell,
					(t_file *)redir->content, hd) == -1)
				return (-1);
			hd = hd->next;
			if (redir)
				redir = redir->next;
		}
		node = node->next;
	}
	return (0);
}

void	cleanup_heredocs(t_pipe *pipeline)
{
	t_pipe	*node;
	t_list	*redir;
	t_file	*file;

	node = pipeline;
	while (node)
	{
		redir = node->redirs;
		while (redir)
		{
			file = (t_file *)redir->content;
			if (file->filename
				&& ft_strnstr(file->filename, "/tmp/minishell_hd", 16))
				unlink(file->filename);
			redir = redir->next;
		}
		node = node->next;
	}
}
