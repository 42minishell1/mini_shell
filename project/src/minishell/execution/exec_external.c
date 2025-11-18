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

void	exec_external(t_shell *shell, t_pipe *node)
{
	if (!node->cmd || !node->cmd[0])
		exit(0);
	execve(node->cmd[0], node->cmd, shell->envp);
	perror(node->cmd[0]);
	exit(127);
}
