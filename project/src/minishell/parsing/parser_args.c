/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_args.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaehlee <jaehlee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/16 22:10:22 by jaehlee           #+#    #+#             */
/*   Updated: 2025/10/24 17:44:18 by jaehlee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* NULL 종료된 문자열 배열 길이를 구한다 */
static size_t	str_array_len(char **array)
{
	size_t	count;

	count = 0;
	while (array && array[count])
		count++;
	return (count);
}

/* 기존 포인터들을 새 배열로 복사한다 */
static void	copy_existing(char **dst, char **src, size_t count)
{
	size_t	index;

	index = 0;
	while (index < count)
	{
		dst[index] = src[index];
		index++;
	}
}

/* 문자열 배열을 한 칸 확장할 새 버퍼를 만든다 */
static char	**extend_array(char **src, size_t count)
{
	char	**updated;

	updated = (char **)malloc(sizeof(char *) * (count + 2));
	if (!updated)
	{
		errno = ENOMEM;
		return (NULL);
	}
	copy_existing(updated, src, count);
	return (updated);
}

/* 문자열 배열 끝에 새 단어를 추가한다 */
int	append_word(char ***array, const char *word)
{
	char	**old;
	char	**extended;
	size_t	count;

	if (!array || !word)
		return (-1);
	old = *array;
	count = str_array_len(old);
	extended = extend_array(old, count);
	if (!extended)
		return (-1);
	extended[count] = ft_strdup(word);
	if (!extended[count])
	{
		free(extended);
		errno = ENOMEM;
		return (-1);
	}
	extended[count + 1] = NULL;
	free(old);
	*array = extended;
	return (0);
}

/* 문자열 배열과 내부 문자열들을 해제한다 */
void	free_str_array(char **array)
{
	size_t	index;

	if (!array)
		return ;
	index = 0;
	while (array[index])
	{
		free(array[index]);
		index++;
	}
	free(array);
}
