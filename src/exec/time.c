/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:18:35 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/23 15:20:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

double	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

double	calc_timeframe(t_game *game)
{
	double	now;
	double	frame_time;

	now = get_time();
	frame_time = (now - game->last_time) / 1000.0;
	if (frame_time > 0.05f)
		frame_time = 0.05f;
	if (frame_time < 0.001f)
		frame_time = 0.001f;
	game->last_time = now;
	game->delta_time = frame_time;
	return (frame_time);
}