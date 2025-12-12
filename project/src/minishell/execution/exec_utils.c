/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:30:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:30:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 파이프 FD 배열을 사용하지 않는 상태로 초기화한다.
void	pipe_reset(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
}

// 파이프라인 없이 단독 실행되는 빌트인인지 확인한다.
int	is_isolated_builtin(t_pipe *node, int prev_fd)
{
	if (!node || !is_builtin(node->cmd))
		return (0);
	if (node->next)
		return (0);
	if (prev_fd != -1)
		return (0);
	return (1);
}

// 부모 프로세스에서 처리해야 하는 빌트인 명령인지 판별한다.
static int	is_parent_builtin(t_pipe *node)
{
	if (!node || !node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (1);
	if (ft_strcmp(node->cmd[0], "export") == 0)
		return (1);
	if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (1);
	if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (1);
	return (0);
}

// 표준 입출력을 저장된 FD로 복구한다.
static void	restore_stdio(int saved_in, int saved_out)
{
	if (saved_in != -1)
	{
		dup2(saved_in, STDIN_FILENO);
		close(saved_in);
	}
	if (saved_out != -1)
	{
		dup2(saved_out, STDOUT_FILENO);
		close(saved_out);
	}
}

// 단독 빌트인일 경우 부모에서 리다이렉션을 열고 실행한 뒤 상태를 반환한다.
int	handle_parent_builtin(t_shell *shell, t_pipe **node, int prev_fd)
{
	int	saved_in;
	int	saved_out;

	if (!is_isolated_builtin(*node, prev_fd) || !is_parent_builtin(*node))
		return (0);
	saved_in = dup(STDIN_FILENO);
	saved_out = dup(STDOUT_FILENO);
	if (saved_in == -1 || saved_out == -1)
		return (close(saved_in), close(saved_out), -1);
	if (open_redir(*node) == -1)
	{
		close_redir(*node);
		restore_stdio(saved_in, saved_out);
		shell->last_status = 1;
		*node = (*node)->next;
		return (1);
	}
	shell->last_status = run_builtin_parent(shell, *node);
	close_redir(*node);
	restore_stdio(saved_in, saved_out);
	*node = (*node)->next;
	return (1);
}
