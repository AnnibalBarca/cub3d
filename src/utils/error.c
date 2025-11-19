/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:19:48 by nagaudey          #+#    #+#             */
/*   Updated: 2025/11/19 17:45:15 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	print_e(char *str, int status)
{
	ft_putstr_fd("Error\n", 2);
	if (str)
		ft_putstr_fd(str, 2);
	return (status);
}

int	count_commas(char *line)
{
	int	count;
	int	i;

	i = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == ',')
			count++;
		i++;
	}
	if (count == 2)
		return (1);
	return (0);
}
