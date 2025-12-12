/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 17:07:53 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 17:07:53 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 주어진 명령이 지원되는 빌트인인지 판별한다. */
int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if ((ft_strcmp(cmd[0], "echo") == 0) || (ft_strcmp(cmd[0], "cd") == 0) \
		|| (ft_strcmp(cmd[0], "pwd") == 0) \
		|| (ft_strcmp(cmd[0], "export") == 0) \
		|| (ft_strcmp(cmd[0], "env") == 0) \
		|| (ft_strcmp(cmd[0], "unset") == 0) \
		|| (ft_strcmp(cmd[0], "exit") == 0))
		return (1);
	return (0);
}

/* 부모 프로세스에서만 실행되어야 하는 빌트인을 수행한다. */
int	run_builtin_parent(t_shell *shell, t_pipe *node)
{
	if (!node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (cd(shell, node));
	if (ft_strcmp(node->cmd[0], "export") == 0)
		return (export(shell, node));
	if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (unset(shell, node));
	if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (exit_builtin(shell, node));
	return (-1);
}

/* 자식 프로세스에서도 안전하게 실행 가능한 빌트인을 수행한다. */
int	run_builtin_child(t_shell *shell, t_pipe *node)
{
	if (!node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (echo(node));
	if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (pwd(node));
	if (ft_strcmp(node->cmd[0], "env") == 0)
		return (env_builtin(shell, node));
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (cd(shell, node));
	if (ft_strcmp(node->cmd[0], "export") == 0)
		return (export(shell, node));
	if (ft_strcmp(node->cmd[0], "unset") == 0)
		return (unset(shell, node));
	if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (exit_builtin(shell, node));
	return (-1);
}
