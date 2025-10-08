/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 14:32:35 by almeekel          #+#    #+#             */
/*   Updated: 2024/11/20 14:47:06 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*tmp;
	unsigned char	uc;

	uc = (unsigned char)c;
	tmp = (unsigned char *)s;
	while (n--)
	{
		if (*tmp == uc)
			return (tmp);
		tmp++;
	}
	return (NULL);
}
