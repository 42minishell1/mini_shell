/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 14:18:58 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:05:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 인자가 모두 -n 형식인지 확인해 개행 억제 옵션 여부를 판별한다.
static int	is_nflag(char *s)
{
	int	i;

	if (!s || s[0] != '-' || s[1] == '\0')
		return (0);
	i = 0;
	while (s[++i])
		if (s[i] != 'n')
			return (0);
	return (1);
}

// echo 빌트인: -n 옵션을 처리해 인자를 출력한다.
int	echo(t_pipe *node)
{
	int		i;
	int		nl;
	char	**av;

	if (!node || !node->cmd)
		return (0);
	av = node->cmd;
	i = 1;
	nl = 1;
	while (av[i] && is_nflag(av[i]))
	{
		nl = 0;
		i++;
	}
	while (av[i])
	{
		write(STDOUT_FILENO, av[i], ft_strlen(av[i]));
		if (av[i + 1])
			write(STDOUT_FILENO, " ", 1);
		i++;
	}
	if (nl)
		write(STDOUT_FILENO, "\n", 1);
	return (0);
}
