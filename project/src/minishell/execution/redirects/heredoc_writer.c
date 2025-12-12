/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_writer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 15:41:38 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 15:41:38 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// heredoc 입력을 프롬프트로 받아 구분자 전까지 파일에 기록한다.
int	write_heredoc_body(t_shell *shell, const char *delimit, int quoted, int fd)
{
	char	*line;
	char	*expanded;

	while (1)
	{
		line = readline("> ");
		if (!line || ft_strcmp(line, delimit) == 0)
			break ;
		if (!quoted)
			expanded = expand_str_simple(shell, line);
		else
			expanded = ft_strdup(line);
		if (!expanded)
			return (free(line), -1);
		write(fd, expanded, ft_strlen(expanded));
		write(fd, "\n", 1);
		free(expanded);
		free(line);
	}
	free(line);
	return (0);
}
