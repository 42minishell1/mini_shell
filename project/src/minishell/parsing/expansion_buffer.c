/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_buffer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:05:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 12:05:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* 버퍼 문자열 뒤에 새 값을 붙이고 메모리를 교체한다. */
int	append_value(char **buf, char *val)
{
	char	*joined;

	if (!val)
		return (-1);
	joined = ft_strjoin(*buf, val);
	free(*buf);
	free(val);
	*buf = joined;
	if (!joined)
		return (-1);
	return (0);
}

/* 누적 버퍼를 최종 단어 배열에 추가한다. */
int	append_buffer(char ***out, char *buf)
{
	if (!buf || buf[0] == '\0')
	{
		free(buf);
		return (0);
	}
	if (append_word(out, buf) == -1)
		return (free(buf), -1);
	free(buf);
	return (0);
}

/* 현재 버퍼를 배열에 옮기고 빈 문자열로 초기화한다. */
int	flush_buffer(char ***out, char **buf)
{
	int	ret;

	ret = append_buffer(out, *buf);
	*buf = ft_strdup("");
	return (ret);
}

/* 공백을 만나면 버퍼를 비우고 단어 경계를 만든다. */
int	handle_space(char ***out, char **buf)
{
	if (flush_buffer(out, buf) == -1)
		return (-1);
	return (0);
}

/* 인용 여부에 따라 단어 조각을 버퍼에 추가하거나 나눈다. */
int	add_word_part(char ***out, char **buf, char *val, int quoted)
{
	size_t	i;

	if (quoted)
		return (append_value(buf, val));
	i = 0;
	while (val && val[i])
	{
		if (is_space((unsigned char)val[i]))
		{
			if (flush_buffer(out, buf) == -1)
				return (free(val), -1);
			while (val[i] && is_space((unsigned char)val[i]))
				i++;
			continue ;
		}
		if (push_char(buf, val[i]) == -1)
			return (free(val), -1);
		i++;
	}
	free(val);
	return (0);
}
