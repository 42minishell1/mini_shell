/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline_child.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 20:17:41 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 20:17:41 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	pipeline_child_process(t_shell *shell, t_pipe *node,
			int prev_fd, int pipefd[2])
{
	setup_child_signals();
	if (prev_fd != -1)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (node->next)
	{
		close(pipefd[0]);
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
	if (open_redir(node) == -1)
		exit(1);
	if (is_builtin(node->cmd))
		exit(run_builtin_child(shell, node));
	exec_external(shell, node);
}

void	pipeline_parent_after_fork(int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
}
