/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_hex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:02:06 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:04:35 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_hex(unsigned long n, int is_upper, int *count)
{
	char	*base;

	if (is_upper)
		base = "0123456789ABCDEF";
	else
		base = "0123456789abcdef";
	if (n >= 16)
		if (print_hex(n / 16, is_upper, count))
			return (1);
	if (print_char(base[n % 16], count))
		return (1);
	return (0);
}
