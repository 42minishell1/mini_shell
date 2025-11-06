/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_segment.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/17 12:34:11 by jaehlee           #+#    #+#             */
/*   Updated: 2025/09/17 12:34:11 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 현재 토큰이 리다이렉션이면 파이프 노드를 갱신한다 */
static int	handle_redirection(t_pipe *pipe, t_list *node)
{
	t_tok	*redir;
	t_tok	*word;
	int		status;

	if (!node || !node->next)
		return (PARSE_SYNTAX_ERROR);
	redir = (t_tok *)node->content;
	word = (t_tok *)node->next->content;
	if (!word || word->type != T_WORD)
		return (PARSE_SYNTAX_ERROR);
	if (redir->type == T_LT)
		return (set_file(&pipe->infile, word->value, F_IN, 0));
	if (redir->type == T_GT)
		return (set_file(&pipe->outfile, word->value, F_OUT_TRUNC, 0));
	if (redir->type == T_DGT)
		return (set_file(&pipe->outfile, word->value, F_OUT_APPEND, 0));
	if (redir->type != T_DLT)
		return (PARSE_SYNTAX_ERROR);
	status = append_heredoc_node(pipe, word->value, 0);
	if (status != PARSE_OK)
		return (status);
	return (set_file(&pipe->infile, word->value, F_HEREDOC, 0));
}

/* 리다이렉션 기호와 그 피연산자를 건너뛴다 */
static t_list	*skip_redirection(t_list *node)
{
	if (!node)
		return (NULL);
	if (!node->next)
		return (NULL);
	return (node->next->next);
}

/* 단어 토큰을 명령 인자 배열에 추가한다 */
static int	add_word_token(t_pipe *pipe, t_list **node)
{
	t_tok	*token;

	token = (t_tok *)(*node)->content;
	if (append_word(&pipe->cmd, token->value) == -1)
		return (PARSE_ALLOC_ERROR);
	*node = (*node)->next;
	return (PARSE_OK);
}

/* 파이프 구분 전까지 토큰을 읽어 한 세그먼트를 구성한다 */
int	parse_segment(t_pipe *pipe, t_list **cursor)
{
	t_list	*node;
	int		status;

	node = *cursor;
	while (node)
	{
		if (!node->content || ((t_tok *)node->content)->type == T_PIPE)
			break ;
		if (((t_tok *)node->content)->type == T_WORD)
		{
			status = add_word_token(pipe, &node);
			if (status != PARSE_OK)
				return (status);
			continue ;
		}
		status = handle_redirection(pipe, node);
		if (status != PARSE_OK)
			return (status);
		node = skip_redirection(node);
	}
	*cursor = node;
	return (PARSE_OK);
}
