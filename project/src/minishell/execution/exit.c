/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:05:10 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:12:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_numeric(const char *s)
{
	int	i;

	if (!s || s[0] == '\0')
		return (0);
	i = 0;
	if (s[i] == '+' || s[i] == '-')
		i++;
	if (!ft_isdigit(s[i]))
		return (0);
	while (s[i])
	{
		if (!ft_isdigit(s[i]))
			return (0);
		i++;
	}
	return (1);
}

static unsigned char	to_status(const char *s)
{
	long long	value;
	int			sign;
	int			i;

	value = 0;
	sign = 1;
	i = 0;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -1;
		i++;
	}
	while (ft_isdigit(s[i]))
	{
		value = value * 10 + (s[i] - '0');
		i++;
	}
	return ((unsigned char)(value * sign));
}

int	exit_builtin(t_shell *shell, t_pipe *tool)
{
	unsigned char	code;

	code = 0;
	if (shell)
		code = (unsigned char)shell->last_status;
	ft_putendl_fd("exit", STDOUT_FILENO);
	if (!tool || !tool->cmd || !tool->cmd[1])
		exit(code);
	if (!is_numeric(tool->cmd[1]))
	{
		ft_putendl_fd("minishell: exit: numeric argument required",
			STDERR_FILENO);
		exit(2);
	}
	if (tool->cmd[2])
		return (ft_putendl_fd("minishell: exit: too many arguments",
				STDERR_FILENO), 1);
	code = to_status(tool->cmd[1]);
	exit(code);
}
