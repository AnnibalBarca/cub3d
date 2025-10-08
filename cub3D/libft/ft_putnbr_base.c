/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:44:08 by Mimoulapino       #+#    #+#             */
/*   Updated: 2025/02/21 21:24:48 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_nblen(long long nb, int baselen)
{
	int	len;

	len = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = -nb;
		len++;
	}
	while (nb != 0)
	{
		nb /= baselen;
		len++;
	}
	return (len);
}

static void	ft_putnbr_base(char *base, long long nb, int len)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb >= len)
	{
		ft_putnbr_base(base, nb / len, len);
	}
	write(1, &base[nb % len], 1);
}

int	ft_nbshow(char *base, long long nb, int len)
{
	ft_putnbr_base(base, nb, len);
	return (ft_nblen(nb, len));
}

// int	main(void)
// {
// 	printf ("\n%d\n", ft_nbshow("0123456789", 16, 10));
// }
