/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 15:42:58 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/07 15:44:06 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	get_minimap_cell_color(t_game *game, char c)
{
	int	r;
	int	g;
	int	b;

	if (c == '1')
	{
		r = game->ceiling_color.r;
		g = game->ceiling_color.g;
		b = game->ceiling_color.b;
		return ((r << 16) | (g << 8) | b);
	}
	if (c == '0' || c == 'N' || c == 'S' || c == 'E' || c == 'W')
	{
		r = game->floor_color.r;
		g = game->floor_color.g;
		b = game->floor_color.b;
		return ((r << 16) | (g << 8) | b);
	}
	return (0x000000);
}

void	init_mmap(t_game *game)
{
	game->mmap.cx = game->screen_width - MINIMAP_RADIUS - 20;
	game->mmap.cy = MINIMAP_RADIUS + 20;
	game->mmap.radius = MINIMAP_RADIUS;
	game->mmap.scale = 10;
	game->mmap.map_width = game->map_width;
	game->mmap.map_height = game->map_height;
	game->mmap.px = 0;
	game->mmap.py = 0;
}
