/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_state.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:35:44 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 14:35:44 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 배열을 깊은 복사한다.
static char	**dup_envp(char **envp)
{
	size_t	count;
	size_t	i;
	char	**copy;

	count = 0;
	i = -1;
	while (envp[count])
		count++;
	copy = (char **)ft_calloc(count + 1, sizeof(char *));
	if (!copy)
		return (NULL);
	while (++i < count)
	{
		copy[i] = ft_strdup(envp[i]);
		if (!copy[i])
		{
			free_str_array(copy);
			return (NULL);
		}
	}
	return (copy);
}

// 셸 구조체를 초기화하고 기본 FD 백업을 만든다.
void	init_shell(t_shell *shell, char **envp)
{
	ft_bzero(shell, sizeof(*shell));
	shell->envp = dup_envp(envp);
	if (!shell->envp)
	{
		perror("minishell");
		exit(EXIT_FAILURE);
	}
	shell->stdin_backup = dup(STDIN_FILENO);
	shell->stdout_backup = dup(STDOUT_FILENO);
	if (shell->stdin_backup == -1 || shell->stdout_backup == -1)
	{
		perror("minishell");
		destroy_shell(shell);
		exit(EXIT_FAILURE);
	}
	shell->last_status = 0;
}

// 셸 자원을 해제하고 표준 입출력을 복원한다.
void	destroy_shell(t_shell *shell)
{
	if (!shell)
		return ;
	if (shell->stdin_backup != -1)
	{
		dup2(shell->stdin_backup, STDIN_FILENO);
		close(shell->stdin_backup);
		shell->stdin_backup = -1;
	}
	if (shell->stdout_backup != -1)
	{
		dup2(shell->stdout_backup, STDOUT_FILENO);
		close(shell->stdout_backup);
		shell->stdout_backup = -1;
	}
	free_str_array(shell->envp);
	shell->envp = NULL;
}
