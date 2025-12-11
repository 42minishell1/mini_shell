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
static int	handle_redirection(t_shell *shell, t_pipe *pipe, t_list *node)
{
	t_tok	*redir;
	t_tok	*word;
	int		quoted;

	if (!node || !node->next)
		return (PARSE_SYNTAX_ERROR);
	redir = (t_tok *)node->content;
	word = (t_tok *)node->next->content;
	if (!word || word->type != T_WORD)
		return (PARSE_SYNTAX_ERROR);
	quoted = is_quoted_word(word->value);
	if (redir->type == T_DLT)
		return (process_heredoc(pipe, word, quoted));
	return (process_file_redir(shell, pipe, redir, word));
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
static int	add_word_token(t_shell *shell, t_pipe *pipe, t_list **node)
{
	t_tok	*token;
	char	**expanded;
	int		i;
	int		status;

	token = (t_tok *)(*node)->content;
	expanded = NULL;
	status = expand_word(shell, token->value, &expanded);
	if (status != PARSE_OK)
		return (status);
	i = 0;
	while (expanded && expanded[i])
	{
		if (append_word(&pipe->cmd, expanded[i]) == -1)
			return (free_str_array(expanded), PARSE_ALLOC_ERROR);
		i++;
	}
	free_str_array(expanded);
	*node = (*node)->next;
	return (PARSE_OK);
}

/* 파이프 구분 전까지 토큰을 읽어 한 세그먼트를 구성한다 */
int	parse_segment(t_shell *shell, t_pipe *pipe, t_list **cursor)
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
			status = add_word_token(shell, pipe, &node);
			if (status != PARSE_OK)
				return (status);
			continue ;
		}
		status = handle_redirection(shell, pipe, node);
		if (status != PARSE_OK)
			return (status);
		node = skip_redirection(node);
	}
	*cursor = node;
	return (PARSE_OK);
}
