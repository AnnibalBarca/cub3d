/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alexandremeekel-konjikovic <alexandreme    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/23 23:31:00 by alexandreme       #+#    #+#             */
/*   Updated: 2024/06/02 12:53:04 by alexandreme      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t n)
{
	size_t				i;
	unsigned char		*dest;
	const unsigned char	*source;

	source = (const unsigned char *)src;
	dest = (unsigned char *)dst;
	if (dest < source)
	{
		i = 0;
		while (i < n)
		{
			dest[i] = source[i];
			i++;
		}
	}
	else
	{
		while (n--)
			dest[n] = source[n];
	}
	return (dst);
}
// if (dest == source || n == 0)
	// 	return (dst);
