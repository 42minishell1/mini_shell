/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:20:39 by jaemyu            #+#    #+#             */
/*   Updated: 2025/12/06 14:28:58 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 현재 파이프 노드를 실행할 자식을 만들고 파이프를 설정한다.
static int	start_child_process(t_shell *shell, t_pipe *node,
			pid_t *slot, int *prev_fd)
{
	int	pipefd[2];

	if (!node->next)
		pipe_reset(pipefd);
	else if (pipe(pipefd) == -1)
		return (-1);
	*slot = fork();
	if (*slot == -1)
		return (-1);
	if (*slot == 0)
		pipeline_child_process(shell, node, *prev_fd, pipefd);
	pipeline_parent_after_fork(prev_fd, pipefd);
	return (0);
}

// 부모 빌트인을 우선 처리하고 필요 시 자식 프로세스를 띄운다.
static int	process_pipeline_node(t_shell *shell, t_pipe **node,
			pid_t *slot, int *prev_fd)
{
	int	result;

	result = handle_parent_builtin(shell, node, *prev_fd);
	if (result == -1)
		return (-1);
	if (result == 1 || !*node)
		return (1);
	if (start_child_process(shell, *node, slot, prev_fd) == -1)
		return (-1);
	*node = (*node)->next;
	return (0);
}

// 파이프라인 전체를 순회하며 제한 안에서 프로세스를 생성한다.
static int	run_pipeline_loop(t_shell *shell, t_pipe *node,
			pid_t *pids, int *count_out)
{
	int	prev_fd;
	int	count;
	int	res;

	prev_fd = -1;
	count = 0;
	while (node && count < PIPE_LIMIT)
	{
		res = process_pipeline_node(shell, &node, &pids[count], &prev_fd);
		if (res == -1)
		{
			if (prev_fd != -1)
				close(prev_fd);
			return (-1);
		}
		if (res == 0)
			count++;
	}
	if (prev_fd != -1)
		close(prev_fd);
	*count_out = count;
	if (node && count >= PIPE_LIMIT)
		return (-1);
	return (0);
}

// heredoc 준비 후 파이프라인을 실행하고 자식 종료 상태를 모은다.
int	execute_pipeline(t_shell *shell, t_pipe *pipeline)
{
	t_pipe	*node;
	pid_t	pids[PIPE_LIMIT];
	int		count;
	int		status;

	if (prepare_heredocs(shell, pipeline) == -1)
		return (-1);
	node = pipeline;
	count = 0;
	status = run_pipeline_loop(shell, node, pids, &count);
	if (status == -1)
	{
		cleanup_heredocs(pipeline);
		return (-1);
	}
	cleanup_heredocs(pipeline);
	if (count == 0)
		return (shell->last_status);
	return (wait_pipeline(pids, count, shell));
}
