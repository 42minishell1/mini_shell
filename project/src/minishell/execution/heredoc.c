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

	node = pipeline;
	while (node)
	{
		hd = node->herelist;
		while (hd)
		{
			if (process_single_heredoc(shell, node, hd) == -1)
				return (-1);
			hd = hd->next;
		}
		node = node->next;
	}
	return (0);
}

void	cleanup_heredocs(t_pipe *pipeline)
{
	t_pipe	*node;
	char	*name;

	node = pipeline;
	while (node)
	{
		if (node->infile && node->infile->type == F_IN
			&& node->infile->filename)
		{
			name = node->infile->filename;
			if (ft_strnstr(name, "/tmp/minishell_hd", 16))
				unlink(name);
		}
		node = node->next;
	}
}
