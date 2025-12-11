/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_word.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:10:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 12:10:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

typedef struct s_expctx
{
	size_t	i;
	int		quote;
	char	*buf;
}	t_expctx;

static int	handle_quote(char c, t_expctx *ctx)
{
	if ((c == '\'' || c == '\"') && ctx->quote == 0)
		return (ctx->quote = c, 1);
	if (ctx->quote && c == ctx->quote)
		return (ctx->quote = 0, 1);
	return (0);
}

static int	handle_dollar(t_shell *shell, const char *src, t_expctx *ctx,
			char ***out)
{
	char	*val;

	if (src[ctx->i] != '$' || ctx->quote == '\'')
		return (1);
	val = expand_dollar(shell, src, &ctx->i);
	if (!val)
		return (PARSE_ALLOC_ERROR);
	if (add_word_part(out, &ctx->buf, val, ctx->quote == '\"') == -1)
		return (PARSE_ALLOC_ERROR);
	return (PARSE_OK);
}

static int	process_expansion(t_shell *shell, const char *src, t_expctx *ctx,
			char ***out)
{
	char	c;
	int		status;

	c = src[ctx->i];
	if (handle_quote(c, ctx))
		return (PARSE_OK);
	status = handle_dollar(shell, src, ctx, out);
	if (status != 1)
		return (status);
	if (is_space((unsigned char)c) && ctx->quote == 0)
	{
		if (handle_space(out, &ctx->buf) == -1)
			return (PARSE_ALLOC_ERROR);
		return (PARSE_OK);
	}
	if (push_char(&ctx->buf, c) == -1)
		return (PARSE_ALLOC_ERROR);
	return (PARSE_OK);
}

int	expand_word(t_shell *shell, const char *src, char ***out)
{
	t_expctx	ctx;
	int			status;

	if (!out || !src)
		return (PARSE_SYNTAX_ERROR);
	*out = NULL;
	ctx.buf = ft_strdup("");
	if (!ctx.buf)
		return (PARSE_ALLOC_ERROR);
	ctx.quote = 0;
	ctx.i = 0;
	while (src[ctx.i])
	{
		status = process_expansion(shell, src, &ctx, out);
		if (status != PARSE_OK)
			return (free(ctx.buf), status);
		ctx.i++;
	}
	if (ctx.quote)
		return (free(ctx.buf), PARSE_SYNTAX_ERROR);
	if (append_buffer(out, ctx.buf) == -1)
		return (PARSE_ALLOC_ERROR);
	return (PARSE_OK);
}
