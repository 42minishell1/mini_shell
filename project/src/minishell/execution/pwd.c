/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 15:25:23 by jaemyu            #+#    #+#             */
/*   Updated: 2025/09/17 15:25:23 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// pwd 빌트인: 현재 작업 디렉토리를 출력한다.
int	pwd(t_pipe *node)
{
	char	*cwd;

	(void)node;
	cwd = getcwd(NULL, 0);
	if (!cwd)
	{
		perror("minishell: pwd");
		return (1);
	}
	ft_putendl_fd(cwd, STDOUT_FILENO);
	free(cwd);
	return (0);
}
