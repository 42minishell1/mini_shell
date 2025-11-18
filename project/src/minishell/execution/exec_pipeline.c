/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_pipeline.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:20:39 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/17 14:20:39 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	exec_pipe(t_shell *shell, t_pipe *pipeline)
{
	if (prepare_heredocs(shell, pipeline) == -1)
		return (-1);
	cleanup_heredocs(pipeline);
	return (0);
}