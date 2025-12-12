/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_redir.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 19:45:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/12/12 19:45:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*file_new(const char *filename, t_ftype type, int quoted)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	if (!file)
	{
		errno = ENOMEM;
		return (NULL);
	}
	file->filename = ft_strdup(filename);
	if (!file->filename)
	{
		free(file);
		errno = ENOMEM;
		return (NULL);
	}
	file->type = type;
	file->quoted = quoted;
	return (file);
}

static int	append_redir(t_pipe *pipe, t_file *file)
{
	t_list	*node;

	node = ft_lstnew(file);
	if (!node)
	{
		free(file->filename);
		free(file);
		errno = ENOMEM;
		return (PARSE_ALLOC_ERROR);
	}
	ft_lstadd_back(&pipe->redirs, node);
	return (PARSE_OK);
}

int	set_file(t_pipe *pipe, t_file **slot, t_file *file)
{
	if (!pipe || !slot || !file || !file->filename)
		return (PARSE_SYNTAX_ERROR);
	if (append_redir(pipe, file) == PARSE_ALLOC_ERROR)
		return (PARSE_ALLOC_ERROR);
	*slot = file;
	return (PARSE_OK);
}
