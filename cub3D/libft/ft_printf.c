/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:05:40 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/02/21 21:24:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

static int	ft_checker(char format, va_list args)
{
	if (format == 's')
		return (ft_putchar_len(va_arg(args, char *)));
	if (format == 'c')
		return (ft_putchar(va_arg(args, int)));
	if (format == 'd' || format == 'i')
		return (ft_nbshow("0123456789", va_arg(args, int), 10));
	if (format == 'u')
		return (ft_nbshow("0123456789", va_arg(args, unsigned int), 10));
	if (format == 'x')
		return (ft_nbshow("0123456789abcdef", va_arg(args, unsigned int), 16));
	if (format == 'X')
		return (ft_nbshow("0123456789ABCDEF", va_arg(args, unsigned int), 16));
	if (format == 'p')
		return (ft_nbshow_ptr("0123456789abcdef", va_arg(args,
					unsigned long long), 16));
	return (write(1, &format, 1));
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		len;

	len = 0;
	va_start(args, format);
	while (*format)
	{
		if (*format == '%')
		{
			len += ft_checker(*(format + 1), args);
			format++;
		}
		else
		{
			len += write(1, format, 1);
		}
		format++;
	}
	va_end(args);
	return (len);
}

// int	main(void)
// {
// 	printf ("\n%d\n", ft_printf("%d4574", 16));
// }
