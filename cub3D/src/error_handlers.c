/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 10:58:42 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/13 10:58:45 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"
#include <stdio.h>
#include <stdlib.h>

void	error_exit(const char *msg, t_game *game)
{
	(void)game;
	printf("Error\n%s\n", msg);
	exit(1);
}

void	error_message(const char *msg)
{
	printf("Error\n%s\n", msg);
}
