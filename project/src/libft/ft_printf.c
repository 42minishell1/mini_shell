/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:15:42 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/17 01:02:38 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	check_type(char c, va_list arg, int *count)
{
	if (c == 'c')
		return (print_char(va_arg(arg, int), count));
	else if (c == 's')
		return (print_str(va_arg(arg, char *), count));
	else if (c == 'p')
		return (print_ptr((unsigned long)va_arg(arg, void *), count));
	else if (c == 'd' || c == 'i')
		return (print_nbr(va_arg(arg, int), count));
	else if (c == 'u')
		return (print_unbr(va_arg(arg, unsigned int), count));
	else if (c == 'x')
		return (print_hex(va_arg(arg, unsigned int), 0, count));
	else if (c == 'X')
		return (print_hex(va_arg(arg, unsigned int), 1, count));
	else if (c == '%')
		return (print_char('%', count));
	else
		return (1);
}

int	ft_printf(const char *format, ...)
{
	va_list	ap;
	int		count;

	count = 0;
	va_start(ap, format);
	while (*format)
	{
		if (*format == '%' && *(format + 1))
		{
			format++;
			if (check_type(*format, ap, &count))
				return (-1);
		}
		else
			if (print_char(*format, &count))
				return (-1);
		format++;
	}
	va_end(ap);
	return (count);
}
