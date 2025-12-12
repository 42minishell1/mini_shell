/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_wait.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/18 19:24:57 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/18 19:24:57 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 파이프라인의 모든 자식을 기다리고 최종 종료코드를 기록한다. */
int	wait_pipeline(pid_t *pids, int count, t_shell *shell)
{
	int	status;
	int	code;
	int	i;

	code = 0;
	i = 0;
	while (i < count)
	{
		if (waitpid(pids[i], &status, 0) == -1)
			status = 1;
		if (WIFEXITED(status))
			code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			code = 128 + WTERMSIG(status);
		i++;
	}
	shell->last_status = code;
	return (code);
}
