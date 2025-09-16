/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/23 17:43:59 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/23 20:15:21 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_strlen(const char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*gnl_strjoin(char *str1, char *str2)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(((gnl_strlen(str1)) + (gnl_strlen(str2))) + 1);
	if (!result)
		return (NULL);
	while (str1 && str1[i])
	{
		result[i] = str1[i];
		i++;
	}
	while (str2 && *str2)
		result[i++] = *(str2++);
	result[i] = '\0';
	if (str1)
	{
		free((void *)str1);
		str1 = NULL;
	}
	return (result);
}

char	*gnl_strdup(char *str)
{
	int		i;
	char	*result;

	i = 0;
	result = (char *)malloc(gnl_strlen(str) + 1);
	if (!result)
		return (NULL);
	while (str && str[i])
	{
		result[i] = str[i];
		i++;
	}
	result[i] = '\0';
	return (result);
}
