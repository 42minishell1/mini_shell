/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_simple.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:15:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 12:15:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 따옴표가 없는 문자열에서 $ 변수만 간단히 확장한다. */
char	*expand_str_simple(t_shell *shell, const char *src)
{
	size_t	i;
	char	*buf;
	char	*val;

	if (!src)
		return (NULL);
	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	i = 0;
	while (src[i])
	{
		if (src[i] == '$'
			&& (src[i + 1] == '?' || is_var_char(src[i + 1])))
		{
			val = expand_dollar(shell, src, &i);
			if (!val || append_value(&buf, val) == -1)
				return (free(buf), NULL);
		}
		else if (push_char(&buf, src[i]) == -1)
			return (free(buf), NULL);
		i++;
	}
	return (buf);
}

/* 문자열에서 따옴표만 제거해 순수 텍스트를 얻는다. */
char	*strip_quotes_only(const char *src)
{
	size_t	i;
	int		quote;
	char	*buf;

	if (!src)
		return (NULL);
	buf = ft_strdup("");
	if (!buf)
		return (NULL);
	quote = 0;
	i = 0;
	while (src[i])
	{
		if ((src[i] == '\'' || src[i] == '\"') && quote == 0)
			quote = src[i];
		else if (quote && src[i] == quote)
			quote = 0;
		else if (push_char(&buf, src[i]) == -1)
			return (free(buf), NULL);
		i++;
	}
	return (buf);
}
