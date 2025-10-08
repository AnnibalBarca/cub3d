/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:17:41 by almeekel          #+#    #+#             */
/*   Updated: 2024/11/21 15:53:30 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *ndl, size_t len)
{
	size_t	i;
	size_t	j;

	if (*ndl == '\0')
		return ((char *)haystack);
	i = 0;
	while (haystack[i] != '\0' && i < len)
	{
		j = 0;
		while (ndl[j] != '\0' && haystack[i + j] == ndl[j] && (i + j) < len)
		{
			j++;
		}
		if (ndl[j] == '\0')
			return ((char *)(haystack + i));
		i++;
	}
	return (NULL);
}
