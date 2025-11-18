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

int	is_builtin(char **cmd)
{
	if (!cmd || !cmd[0])
		return (0);
	if ((ft_strcmp(cmd[0], "echo") == 0) || (ft_strcmp(cmd[0], "cd") == 0) \
		|| (ft_strcmp(cmd[0], "pwd") == 0) \
		|| (ft_strcmp(cmd[0], "export") == 0) \
		|| (ft_strcmp(cmd[0], "env") == 0) || (ft_strcmp(cmd[0], "exit") == 0))
		return (1);
	return (0);
}

int	run_builtin_parent(t_shell *shell, t_pipe *node)
{
	(void)shell;
	if (!node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "cd") == 0)
		return (cd(node));
	if (ft_strcmp(node->cmd[0], "export") == 0)
		return (export(node));
	if (ft_strcmp(node->cmd[0], "exit") == 0)
		return (exit_builtin(node));
	return (-1);
}

int	run_builtin_child(t_shell *shell, t_pipe *node)
{
	(void)shell;
	if (!node->cmd || !node->cmd[0])
		return (0);
	if (ft_strcmp(node->cmd[0], "echo") == 0)
		return (echo(node));
	if (ft_strcmp(node->cmd[0], "pwd") == 0)
		return (pwd(node));
	if (ft_strcmp(node->cmd[0], "env") == 0)
		return (env_builtin(node));
	return (-1);
}
