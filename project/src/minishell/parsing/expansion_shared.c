/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion_shared.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 12:00:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/20 12:00:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// 환경변수 이름에 사용할 수 있는 문자(영문자, 숫자, 언더바)인지 확인한다.
int	is_var_char(int c)
{
	return (ft_isalnum(c) || c == '_');
}

// 종료 상태를 문자열로 변환한다.
static char	*itoa_status(int status)
{
	char	*num;

	num = ft_itoa(status);
	if (!num)
		errno = ENOMEM;
	return (num);
}

// 주어진 키 길이만큼 이름을 잘라 환경 변수 값을 가져온다.
static char	*get_env_value(t_shell *shell, const char *key, size_t len)
{
	char	*name;
	char	*val;

	name = ft_substr(key, 0, len);
	if (!name)
		return (NULL);
	val = env_get(shell->envp, name);
	free(name);
	if (!val)
		return (ft_strdup(""));
	return (ft_strdup(val));
}

// $표현을 읽어 환경 변수 또는 특별 변수(?)로 확장한다.
char	*expand_dollar(t_shell *shell, const char *src, size_t *idx)
{
	size_t	start;
	char	*val;

	start = *idx + 1;
	if (src[start] == '?')
	{
		*idx = start;
		return (itoa_status(shell->last_status));
	}
	while (src[start] && is_var_char(src[start]))
		start++;
	if (start == *idx + 1)
		return (ft_strdup("$"));
	val = get_env_value(shell, src + *idx + 1, start - (*idx + 1));
	*idx = start - 1;
	return (val);
}

// 버퍼 끝에 문자를 하나 붙이고 메모리를 갱신한다.
int	push_char(char **buf, char c)
{
	char	tmp[2];
	char	*joined;

	tmp[0] = c;
	tmp[1] = '\0';
	joined = ft_strjoin(*buf, tmp);
	free(*buf);
	*buf = joined;
	if (!joined)
		return (-1);
	return (0);
}
