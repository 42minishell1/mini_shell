/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 17:26:28 by jaemyu            #+#    #+#             */
/*   Updated: 2025/04/12 01:50:34 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*tmp;

	if (nmemb && size > SIZE_MAX / nmemb)
		return (NULL);
	tmp = malloc(size * nmemb);
	if (!tmp)
		return (NULL);
	ft_memset(tmp, 0, size * nmemb);
	return (tmp);
}
