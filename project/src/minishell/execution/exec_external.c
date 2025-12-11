/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_external.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 18:45:01 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 18:45:01 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*join_path(const char *dir, const char *cmd)
{
	char	*tmp;
	char	*full;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full = ft_strjoin(tmp, cmd);
	free(tmp);
	return (full);
}

static char	*find_in_path(t_shell *shell, char *cmd)
{
	char	*path_env;
	char	**paths;
	char	*full;
	int		i;

	path_env = env_get(shell->envp, "PATH");
	if (!path_env)
		return (NULL);
	paths = ft_split(path_env, ':');
	if (!paths)
		return (NULL);
	i = 0;
	while (paths[i])
	{
		full = join_path(paths[i], cmd);
		if (full && access(full, X_OK) == 0)
			return (free_str_array(paths), full);
		free(full);
		i++;
	}
	free_str_array(paths);
	return (NULL);
}

static void	execve_path(t_shell *shell, t_pipe *node)
{
	char	*path;

	if (ft_strchr(node->cmd[0], '/'))
	{
		execve(node->cmd[0], node->cmd, shell->envp);
		return ;
	}
	path = find_in_path(shell, node->cmd[0]);
	if (path)
	{
		execve(path, node->cmd, shell->envp);
		free(path);
	}
}

void	exec_external(t_shell *shell, t_pipe *node)
{
	if (!node->cmd || !node->cmd[0])
		exit(0);
	execve_path(shell, node);
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}
