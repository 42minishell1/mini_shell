/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:39:08 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:10:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i] && s[i] != '=')
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static int	print_export_env(char **envp)
{
	int	i;

	i = 0;
	while (envp && envp[i])
	{
		ft_putstr_fd("declare -x ", STDOUT_FILENO);
		ft_putendl_fd(envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}

static int	handle_arg(t_shell *shell, char *arg)
{
	char	*eq;
	char	*key;
	int		ret;

	if (!is_valid_key(arg))
		return (ft_putendl_fd("minishell: export: not a valid identifier",
				STDERR_FILENO), 1);
	eq = ft_strchr(arg, '=');
	if (!eq)
		return (0);
	key = ft_substr(arg, 0, eq - arg);
	if (!key)
		return (1);
	ret = env_set(&shell->envp, key, eq + 1);
	free(key);
	return (ret);
}

int	export(t_shell *shell, t_pipe *tool)
{
	int	i;
	int	status;

	if (!tool->cmd || !tool->cmd[0])
		return (0);
	if (!tool->cmd[1])
		return (print_export_env(shell->envp));
	i = 1;
	status = 0;
	while (tool->cmd[i])
	{
		if (handle_arg(shell, tool->cmd[i]))
			status = 1;
		i++;
	}
	return (status);
}
