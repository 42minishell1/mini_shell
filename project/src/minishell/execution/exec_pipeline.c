/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:20:39 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 14:20:39 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define PIPE_LIMIT 256
#define RESET_PIPE(fd) do { (fd)[0] = -1; (fd)[1] = -1; } while (0)
#define IS_ISOLATED_BUILTIN(n, prev) (is_builtin((n)->cmd) && !(n)->next && (prev) == -1)

static void	child_process(t_shell *shell, t_pipe *node, int prev_fd, int pipefd[2])
{
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

static void	parent_after_fork(int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
}

static int	handle_single_builtin(t_shell *shell, t_pipe **node, int prev_fd)
{
	if (!*node || !IS_ISOLATED_BUILTIN(*node, prev_fd))
		return (0);
	if (open_redir(*node) == -1)
		return (-1);
	shell->last_status = run_builtin_parent(shell, *node);
	close_redir(*node);
	*node = (*node)->next;
	return (1);
}

static int	run_pipeline_loop(t_shell *shell, t_pipe *node, pid_t *pids, int *count_out)
{
	int	prev_fd;
	int	pipefd[2];
	int	count;
	int	error;

	prev_fd = -1;
	count = 0;
	error = 0;
	while (node && count < PIPE_LIMIT)
	{
		int	single;

		single = handle_single_builtin(shell, &node, prev_fd);
		if (single == -1)
		{
			error = 1;
			break ;
		}
		if (single == 1)
			continue ;
		if (!node->next)
			RESET_PIPE(pipefd);
		else if (pipe(pipefd) == -1)
		{
			error = 1;
			break ;
		}
		pids[count] = fork();
		if (pids[count] == -1)
		{
			error = 1;
			break ;
		}
		if (pids[count] == 0)
			child_process(shell, node, prev_fd, pipefd);
		parent_after_fork(&prev_fd, pipefd);
		node = node->next;
		count++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	*count_out = count;
	if (error || (node && count >= PIPE_LIMIT))
		return (-1);
	return (0);
}

int	execute_pipeline(t_shell *shell, t_pipe *pipeline)
{
	t_pipe	*node;
	pid_t	pids[PIPE_LIMIT];
	int		count;
	int		status;

	if (prepare_heredocs(shell, pipeline) == -1)
		return (-1);
	node = pipeline;
	status = run_pipeline_loop(shell, node, pids, &count);
	if (status == -1)
	{
		cleanup_heredocs(pipeline);
		return (-1);
	}
	cleanup_heredocs(pipeline);
	return (wait_pipeline(pids, count, shell));
}
