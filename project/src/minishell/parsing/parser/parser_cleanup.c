/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_cleanup.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:34:11 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/17 12:34:11 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 단일 파일 리다이렉션 구조체를 정리한다 */
static void	free_file(t_file *file)
{
	if (!file)
		return ;
	free(file->filename);
	free(file);
}

/* 리다이렉션 리스트를 해제한다 */
static void	free_redirs(t_list *list)
{
	t_list	*next;

	while (list)
	{
		next = list->next;
		free_file((t_file *)list->content);
		free(list);
		list = next;
	}
}

/* heredoc 연결 리스트 전체를 해제한다 */
static void	free_herelist(t_heredoc *list)
{
	t_heredoc	*next;

	while (list)
	{
		next = list->next;
		free(list->delim);
		free(list);
		list = next;
	}
}

/* 파이프라인 전체를 순회하며 모든 자원을 해제한다 */
void	free_pipeline(t_pipe *pipeline)
{
	t_pipe	*next;

	while (pipeline)
	{
		next = pipeline->next;
		free_redirs(pipeline->redirs);
		free_str_array(pipeline->cmd);
		free_herelist(pipeline->herelist);
		free(pipeline);
		pipeline = next;
	}
}
