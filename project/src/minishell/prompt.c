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

void	prompt()
{
	char	*str;

	while (1)
	{
		str = readline("shell : ");
		if (!str)
			break;
		else if (*str)
			add_history(str);
		free(str);
	}
	ft_printf("exit\n");
}