/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:12:24 by jaemyu            #+#    #+#             */
/*   Updated: 2025/09/17 15:12:24 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	update_env_pwd(t_shell *shell, const char *cwd)
{
	char	*old;

	old = env_get(shell->envp, "PWD");
	if (!old)
		old = "";
	if (env_set(&shell->envp, "OLDPWD", old))
		return (1);
	if (env_set(&shell->envp, "PWD", cwd))
		return (1);
	return (0);
}

int	cd(t_shell *shell, t_pipe *node)
{
	char	*target;
	char	*cwd;
	int		ret;

	if (!node->cmd || !node->cmd[0])
		return (1);
	if (!node->cmd[1])
		target = env_get(shell->envp, "HOME");
	else if (node->cmd[2])
		return (ft_putendl_fd("minishell: cd: too many arguments", 2), 1);
	else
		target = node->cmd[1];
	if (!target)
		return (ft_putendl_fd("minishell: cd: HOME not set", 2), 1);
	if (chdir(target) == -1)
		return (perror("minishell: cd"), 1);
	cwd = getcwd(NULL, 0);
	if (!cwd)
		return (perror("minishell: cd"), 1);
	ret = update_env_pwd(shell, cwd);
	free(cwd);
	return (ret);
}
