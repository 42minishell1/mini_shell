/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 15:51:48 by jaemyu            #+#    #+#             */
/*   Updated: 2025/09/16 15:51:48 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	process_line(char *line)
{
	t_pipe	*pipeline;
	int		status;

	pipeline = NULL;
	add_history(line);
	status = parse_line(line, &pipeline);
	if (status == PARSE_ALLOC_ERROR)
		perror("minishell");
	else if (status == PARSE_SYNTAX_ERROR)
		ft_putendl_fd("minishell: syntax error", STDERR_FILENO);
	if (!pipeline)
		return ;
	if (status == PARSE_OK)
	{
		/* 실행부가 pipeline을 받아 실행하도록 연결 예정 */
	}
	free_pipeline(pipeline);
}

void	prompt(void)
{
	char	*str;

	while (1)
	{
		str = readline("shell : ");
		if (!str)
			break ;
		if (*str)
			process_line(str);
		free(str);
	}
	ft_printf("exit\n");
}
