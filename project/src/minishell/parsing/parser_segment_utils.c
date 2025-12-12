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

// 단어 안에 따옴표가 포함되어 있는지 확인한다.
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

// heredoc 토큰을 처리해 파이프 노드에 heredoc 정보와 파일 노드를 추가한다.
int	process_heredoc(t_pipe *pipe, t_tok *word, int quoted)
{
	int		status;
	char	*stripped;
	t_file	*file;

	stripped = strip_quotes_only(word->value);
	if (!stripped)
		return (PARSE_ALLOC_ERROR);
	file = file_new(stripped, F_HEREDOC, quoted);
	if (!file)
		return (free(stripped), PARSE_ALLOC_ERROR);
	status = append_heredoc_node(pipe, stripped, quoted);
	free(stripped);
	if (status != PARSE_OK)
		return (free(file->filename), free(file), status);
	status = set_file(pipe, &pipe->infile, file);
	if (status != PARSE_OK)
	{
		free(file->filename);
		free(file);
	}
	return (status);
}

// 리다이렉션 대상 단어를 확장해 정확히 하나의 토큰만 남겼는지 확인한다.
static int	expand_redir_word(t_shell *shell, t_tok *word,
			char ***expanded, int *quoted)
{
	int	status;

	*quoted = is_quoted_word(word->value);
	*expanded = NULL;
	status = expand_word(shell, word->value, expanded);
	if (status != PARSE_OK)
		return (status);
	if (!*expanded || !(*expanded)[0] || (*expanded)[1])
		return (free_str_array(*expanded), PARSE_SYNTAX_ERROR);
	return (PARSE_OK);
}

// 리다이렉션 타입에 맞춰 대상 파일 포인터를 설정한다.
static int	set_redir_target(t_pipe *pipe, t_tok *redir, t_file *file)
{
	if (redir->type == T_LT)
		return (set_file(pipe, &pipe->infile, file));
	if (redir->type == T_GT)
	{
		file->type = F_OUT_TRUNC;
		return (set_file(pipe, &pipe->outfile, file));
	}
	if (redir->type == T_DGT)
	{
		file->type = F_OUT_APPEND;
		return (set_file(pipe, &pipe->outfile, file));
	}
	return (PARSE_SYNTAX_ERROR);
}

// 일반 파일 리다이렉션을 확장하고 파이프 노드에 연결한다.
int	process_file_redir(t_shell *shell, t_pipe *pipe,
				t_tok *redir, t_tok *word)
{
	char	**expanded;
	int		status;
	int		quoted;
	t_file	*file;

	status = expand_redir_word(shell, word, &expanded, &quoted);
	if (status != PARSE_OK)
		return (status);
	file = file_new(expanded[0], F_IN, quoted);
	if (!file)
		return (free_str_array(expanded), PARSE_ALLOC_ERROR);
	status = set_redir_target(pipe, redir, file);
	if (status != PARSE_OK)
	{
		free(file->filename);
		free(file);
	}
	free_str_array(expanded);
	return (status);
}
