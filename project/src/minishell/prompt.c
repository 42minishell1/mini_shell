/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:51:48 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 16:30:57 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(t_shell *shell, char *line)
{
	t_pipe	*pipeline;
	int		status;
	int		exec_status;

	pipeline = NULL;
	add_history(line);
	status = parse_line(shell, line, &pipeline);
	if (status == PARSE_ALLOC_ERROR)
		perror("minishell");
	else if (status == PARSE_SYNTAX_ERROR)
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	if (!pipeline)
		return ;
	if (status == PARSE_OK)
	{
		exec_status = execute_pipeline(shell, pipeline);
		if (exec_status == -1)
			ft_putendl_fd("minishell: execution failed", STDERR_FILENO);
	}
	free_pipeline(pipeline);
}

void	prompt(t_shell *shell)
{
	char	*str;

	setup_parent_signals();
	while (1)
	{
		str = readline("shell : ");
		if (g_last_signal)
		{
			shell->last_status = g_last_signal;
			g_last_signal = 0;
		}
		if (!str)
			break ;
		if (*str)
			process_line(shell, str);
		free(str);
	}
	ft_printf("exit\n");
}
