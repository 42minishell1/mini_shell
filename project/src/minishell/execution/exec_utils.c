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

/* 파이프 FD 쌍을 초기 sentinel 값으로 리셋한다. */
void	pipe_reset(int fd[2])
{
	fd[0] = -1;
	fd[1] = -1;
}

/* 현재 노드가 포크나 파이프 없이 단독으로 실행 가능한 빌트인인지 확인한다. */
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

/* 셸 상태에 영향을 주므로 부모에서 실행되어야 하는 빌트인인지 확인한다. */
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

/* 부모 빌트인 실행 후 표준 입출력을 원래 상태로 되돌린다. */
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

/* 단독 노드인 부모 빌트인을 리다이렉션 적용 후 실행한다. */
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
		return (restore_stdio(saved_in, saved_out), -1);
	shell->last_status = run_builtin_parent(shell, *node);
	close_redir(*node);
	restore_stdio(saved_in, saved_out);
	*node = (*node)->next;
	return (1);
}
