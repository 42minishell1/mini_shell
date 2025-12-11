/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 10:20:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 10:20:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *s)
{
	int	i;

	if (!s || !(ft_isalpha(s[0]) || s[0] == '_'))
		return (0);
	i = 1;
	while (s[i])
	{
		if (!(ft_isalnum(s[i]) || s[i] == '_'))
			return (0);
		i++;
	}
	return (1);
}

static void	remove_entry(char ***envp, size_t idx)
{
	size_t	i;

	free((*envp)[idx]);
	i = idx;
	while ((*envp)[i])
	{
		(*envp)[i] = (*envp)[i + 1];
		i++;
	}
}

static int	unset_key(char ***envp, const char *key)
{
	size_t	len;
	size_t	i;

	if (!envp || !*envp || !key)
		return (0);
	len = ft_strlen(key);
	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, len) == 0 && (*envp)[i][len] == '=')
		{
			remove_entry(envp, i);
			return (0);
		}
		i++;
	}
	return (0);
}

int	unset(t_shell *shell, t_pipe *tool)
{
	int	i;
	int	status;

	(void)shell;
	if (!tool || !tool->cmd)
		return (0);
	i = 1;
	status = 0;
	while (tool->cmd[i])
	{
		if (!is_valid_key(tool->cmd[i]))
		{
			ft_putendl_fd("minishell: unset: not a valid identifier",
				STDERR_FILENO);
			status = 1;
		}
		else
			unset_key(&shell->envp, tool->cmd[i]);
		i++;
	}
	return (status);
}
