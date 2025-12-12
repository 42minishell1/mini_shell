/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:04:27 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 19:04:27 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// env 빌트인: 인자가 없을 때 현재 환경변수 목록을 출력한다.
int	env_builtin(t_shell *shell, t_pipe *tool)
{
	int	i;

	if (tool->cmd && tool->cmd[1])
		return (ft_putendl_fd("minishell: env: too many arguments",
				STDERR_FILENO), 1);
	if (!shell || !shell->envp)
		return (0);
	i = 0;
	while (shell->envp[i])
	{
		if (ft_strchr(shell->envp[i], '='))
			ft_putendl_fd(shell->envp[i], STDOUT_FILENO);
		i++;
	}
	return (0);
}
