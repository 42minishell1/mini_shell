/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_unbr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/15 15:04:43 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:04:21 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	print_unbr(unsigned int nb, int *count)
{
	if (nb >= 10)
		if (print_unbr(nb / 10, count))
			return (1);
	if (print_char((nb % 10) + '0', count))
		return (1);
	return (0);
}
