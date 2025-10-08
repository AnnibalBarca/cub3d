/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_ptr.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/18 12:44:28 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/02/21 21:24:54 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen_ptr(unsigned long long nb, unsigned int baselen)
{
	unsigned long long	len;

	len = 0;
	while (nb != 0)
	{
		nb /= baselen;
		len++;
	}
	return (len);
}

static void	ft_putptr(char *base, unsigned long long nb, unsigned int len)
{
	if (nb >= len)
	{
		ft_putptr(base, nb / len, len);
	}
	write(1, &base[nb % len], 1);
}

int	ft_nbshow_ptr(char *base, unsigned long long nb, unsigned int len)
{
	if (nb == 0)
		return (write(1, "(nil)", 5));
	write (1, "0x", 2);
	ft_putptr(base, nb, len);
	return (ft_nblen_ptr(nb, len) + 2);
}
