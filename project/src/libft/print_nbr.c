/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_nbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:04:16 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:14:59 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_nbr(int n, int *count)
{
	if (n < 0)
	{
		if (print_char('-', count))
			return (1);
		if (n <= -10 && print_nbr(-(n / 10), count))
			return (1);
		if (print_char('0' - (n % 10), count))
			return (1);
	}
	else
	{
		if (n >= 10)
		{
			if (print_nbr(n / 10, count))
				return (1);
		}
		if (print_char('0' + (n % 10), count))
			return (1);
	}
	return (0);
}
