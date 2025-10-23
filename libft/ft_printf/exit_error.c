/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_error.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/12 23:46:17 by nagaudey          #+#    #+#             */
/*   Updated: 2025/03/13 18:30:31 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../all.h"

int	exit_error(char *str)
{
	char	*succes;
	char	*failure;
	char	*negative;

	succes = "SUCCESS";
	failure = "FAILURE";
	negative = "-1";
	if (str == succes)
		exit(0);
	else if (str == failure)
		exit(1);
	else if (str == negative)
		return (-1);
	else if (write(2, "error in ft_printf_error\n", 24) == -1)
		return (-1);
	return (0);
}
