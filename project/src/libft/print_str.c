/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_str.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:05:20 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:04:10 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_str(char *s, int *count)
{
	int		len;

	if (!s)
		len = write(1, "(null)", 6);
	else
		len = write(1, s, ft_strlen(s));
	if (len == -1)
		return (1);
	*count += len;
	return (0);
}
