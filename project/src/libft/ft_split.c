/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 22:50:10 by jaemyu            #+#    #+#             */
/*   Updated: 2025/08/20 22:43:16 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_word_count(const char *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

static char	*ft_word_dup(const char *start, size_t len)
{
	char	*word;
	size_t	i;

	i = 0;
	word = (char *)malloc(len + 1);
	if (!word)
		return (NULL);
	while (i < len)
	{
		word[i] = start[i];
		i++;
	}
	word[i] = '\0';
	return (word);
}

static char	**ft_free(char **arr, size_t i)
{
	while (i--)
		free(arr[i]);
	free(arr);
	return (NULL);
}

static char	**ft_split_word(char **arr, char const *s, char c)
{
	const char	*start;
	size_t		len;
	size_t		i;

	i = 0;
	while (*s)
	{
		while (*s == c && *s)
			s++;
		if (*s)
		{
			start = s;
			while (*s && *s != c)
				s++;
			len = s - start;
			arr[i] = ft_word_dup(start, len);
			if (!arr[i++])
			{
				ft_free(arr, i);
				return (NULL);
			}
		}
	}
	arr[i] = NULL;
	return (arr);
}

char	**ft_split(char const *s, char c)
{
	char		**arr;
	size_t		count;

	if (!s)
		return (NULL);
	count = ft_word_count(s, c);
	if (! count)
		return (NULL);
	arr = (char **)malloc(sizeof(char *) * (count + 1));
	if (!arr)
		return (NULL);
	return (ft_split_word(arr, s, c));
}
