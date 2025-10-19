/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   len_putstr_error.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 20:50:08 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 00:15:15 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

size_t	len_putstr_error(const char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (write(2, "(null)", 6));
	while (str[i])
	{
		if (write(2, &str[i], 1) == -1)
			return (-1);
		i++;
	}
	return (i);
}
