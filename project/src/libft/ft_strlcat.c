/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 15:10:47 by jaemyu            #+#    #+#             */
/*   Updated: 2025/04/03 15:19:37 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t		srclen;
	size_t		dstlen;
	size_t		i;

	i = 0;
	srclen = 0;
	dstlen = 0;
	while (dst[dstlen] != '\0' && dstlen < size)
		dstlen++;
	while (src[srclen] != '\0')
		srclen++;
	if (dstlen >= size)
		return (size + srclen);
	while (src[i] && dstlen + i + 1 < size)
	{
		dst[dstlen + i] = src[i];
		i++;
	}
	dst[dstlen + i] = '\0';
	return (dstlen + srclen);
}
