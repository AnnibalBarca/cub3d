/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/20 13:27:00 by almeekel          #+#    #+#             */
/*   Updated: 2024/12/09 13:33:59 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	const char		*last_occurrence;
	unsigned char	uc;

	last_occurrence = NULL;
	uc = (unsigned char)c;
	while (*s)
	{
		if (*s == uc)
			last_occurrence = s;
		s++;
	}
	if (uc == '\0')
		return ((char *)s);
	return ((char *)last_occurrence);
}
