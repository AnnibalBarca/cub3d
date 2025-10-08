/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 14:58:49 by almeekel          #+#    #+#             */
/*   Updated: 2024/12/09 13:39:46 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static long int	ft_strtol(const char *str)
{
	long int	result;
	int			sign;
	size_t		i;

	result = 0;
	sign = 1;
	i = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
		if (str[i++] == '-')
			sign = -sign;
	while (str[i] <= '9' && str[i] >= '0')
	{
		if ((result * 10 + str[i] - '0') / 10 != result)
		{
			if (sign == -1)
				return (LONG_MIN);
			return (LONG_MAX);
		}
		result = result * 10 + str[i] - '0';
		i++;
	}
	return (result * sign);
}

int	ft_atoi(const char *str)
{
	return ((int)ft_strtol(str));
}
