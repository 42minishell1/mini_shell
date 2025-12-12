/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 12:00:00 by jaemyu            #+#    #+#             */
/*   Updated: 2025/11/19 12:00:00 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// key에 해당하는 환경변수 값을 찾아 반환한다.
char	*env_get(char **envp, const char *key)
{
	size_t	len;
	int		i;

	if (!envp || !key)
		return (NULL);
	len = ft_strlen(key);
	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], key, len) == 0 && envp[i][len] == '=')
			return (envp[i] + len + 1);
		i++;
	}
	return (NULL);
}

// "KEY=VALUE" 형태의 문자열을 만들어 반환한다.
static char	*build_entry(const char *key, const char *val)
{
	char	*tmp;
	char	*entry;

	tmp = ft_strjoin(key, "=");
	if (!tmp)
		return (NULL);
	entry = ft_strjoin(tmp, val);
	free(tmp);
	return (entry);
}

// 이미 존재하는 키라면 새 엔트리로 교체하고 교체 여부를 반환한다.
static int	replace_existing(char ***envp, const char *key,
			char *entry, size_t len)
{
	int	i;

	i = 0;
	while ((*envp)[i])
	{
		if (ft_strncmp((*envp)[i], key, len) == 0 && (*envp)[i][len] == '=')
		{
			free((*envp)[i]);
			(*envp)[i] = entry;
			return (1);
		}
		i++;
	}
	return (0);
}

// 환경변수 목록에 키를 추가하거나 교체한다.
int	env_set(char ***envp, const char *key, const char *val)
{
	char	*entry;
	size_t	len;

	if (!envp || !key || !val)
		return (1);
	entry = build_entry(key, val);
	if (!entry)
		return (1);
	len = ft_strlen(key);
	if (replace_existing(envp, key, entry, len))
		return (0);
	if (append_word(envp, entry) == -1)
		return (free(entry), 1);
	free(entry);
	return (0);
}
