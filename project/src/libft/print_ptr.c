/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_ptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:05:46 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:01:37 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	creat_string(unsigned long value, int *count)
{
	if (value >= 16)
		if (creat_string(value / 16, count))
			return (1);
	if (print_char("0123456789abcdef"[value % 16], count))
		return (1);
	return (0);
}

int	print_ptr(unsigned long value, int *count)
{
	int		check;

	if (value == 0)
		return (print_str("(nil)", count));
	else
	{
		check = print_str("0x", count);
		if (check == 1)
			return (1);
		return (creat_string(value, count));
	}
}
