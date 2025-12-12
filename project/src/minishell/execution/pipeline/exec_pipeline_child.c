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

// 자식 프로세스에서 파이프 입출력과 리다이렉션을 설정하고 명령을 실행한다.
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

// fork 이후 부모 쪽에서 필요 없는 FD를 정리하고 다음 단계 입력 FD를 남긴다.
void	pipeline_parent_after_fork(int *prev_fd, int pipefd[2])
{
	if (*prev_fd != -1)
		close(*prev_fd);
	if (pipefd[1] != -1)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
}
