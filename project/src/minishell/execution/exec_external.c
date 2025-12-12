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

static char	*join_path(const char *dir, char *cmd)
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
	i = -1;
	while (paths[++i])
	{
		full = join_path(paths[i], cmd);
		if (!full)
			return (free_str_array(paths), NULL);
		if (access(full, X_OK) == 0)
			return (free_str_array(paths), full);
		free(full);
	}
	free_str_array(paths);
	return (NULL);
}

static void	print_exec_error(const char *cmd)
{
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd((char *)cmd, STDERR_FILENO);
	ft_putstr_fd(": ", STDERR_FILENO);
	ft_putendl_fd(strerror(errno), STDERR_FILENO);
}

static void	ensure_exec_access(const char *path, const char *label)
{
	struct stat	st;

	if (stat(path, &st) == -1)
	{
		print_exec_error(label);
		exit(127);
	}
	if (S_ISDIR(st.st_mode))
	{
		errno = EISDIR;
		print_exec_error(label);
		exit(126);
	}
	if (access(path, X_OK) == -1)
	{
		print_exec_error(label);
		exit(126);
	}
}

void	exec_external(t_shell *shell, t_pipe *node)
{
	char	*path;

	if (!node->cmd || !node->cmd[0])
		exit(0);
	if (ft_strchr(node->cmd[0], '/'))
	{
		ensure_exec_access(node->cmd[0], node->cmd[0]);
		execve(node->cmd[0], node->cmd, shell->envp);
		print_exec_error(node->cmd[0]);
		exit(126);
	}
	path = find_in_path(shell, node->cmd[0]);
	if (path)
	{
		ensure_exec_access(path, node->cmd[0]);
		execve(path, node->cmd, shell->envp);
		free(path);
		print_exec_error(node->cmd[0]);
		exit(126);
	}
	ft_putstr_fd("minishell: ", STDERR_FILENO);
	ft_putstr_fd(node->cmd[0], STDERR_FILENO);
	ft_putendl_fd(": command not found", STDERR_FILENO);
	exit(127);
}
