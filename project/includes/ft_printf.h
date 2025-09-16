/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/14 19:16:34 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/15 13:59:07 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include "libft.h"

int	ft_printf(const char *format, ...);
int	print_char(char c, int *count);
int	print_hex(unsigned long n, int upper, int *count);
int	print_nbr(int n, int *count);
int	print_ptr(unsigned long value, int *count);
int	print_str(char *s, int *count);
int	print_unbr(unsigned int nb, int *count);

#endif
