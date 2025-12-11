/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_segment_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:25:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 12:25:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_quoted_word(const char *s)
{
	size_t	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == '\'' || s[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

int	process_heredoc(t_pipe *pipe, t_tok *word, int quoted)
{
	int		status;
	char	*stripped;

	stripped = strip_quotes_only(word->value);
	if (!stripped)
		return (PARSE_ALLOC_ERROR);
	status = append_heredoc_node(pipe, stripped, quoted);
	if (status == PARSE_OK)
		status = set_file(&pipe->infile, stripped, F_HEREDOC, quoted);
	free(stripped);
	return (status);
}

int	process_file_redir(t_shell *shell, t_pipe *pipe,
			t_tok *redir, t_tok *word)
{
	char	**expanded;
	int		status;
	int		quoted;

	quoted = is_quoted_word(word->value);
	expanded = NULL;
	status = expand_word(shell, word->value, &expanded);
	if (status != PARSE_OK)
		return (status);
	if (!expanded || !expanded[0] || expanded[1])
		return (free_str_array(expanded), PARSE_SYNTAX_ERROR);
	if (redir->type == T_LT)
		status = set_file(&pipe->infile, expanded[0], F_IN, quoted);
	else if (redir->type == T_GT)
		status = set_file(&pipe->outfile, expanded[0], F_OUT_TRUNC, quoted);
	else if (redir->type == T_DGT)
		status = set_file(&pipe->outfile, expanded[0], F_OUT_APPEND, quoted);
	else
		status = PARSE_SYNTAX_ERROR;
	free_str_array(expanded);
	return (status);
}
