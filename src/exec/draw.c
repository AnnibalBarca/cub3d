/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:33:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/30 20:10:30 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = game->data.img.addr + (y * game->data.img.line_len + x
			* (game->data.img.bpp / 8));
	*(unsigned int *)pixel = color;
}

int	t_color_to_int(t_color color)
{
	int	rgb;

	rgb = (color.r << 16) | (color.g << 8) | color.b;
	return (rgb);
}

void	draw_floor(t_game *game, int y, unsigned int ceiling,
		unsigned int floor_col)
{
	unsigned int	*pixels;
	int				x;

	pixels = (unsigned int *)game->data.img.addr;
	while (y < WIN_HEIGHT / 2)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixels[y * WIN_WIDTH + x] = ceiling;
			x++;
		}
		y++;
	}
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			pixels[y * WIN_WIDTH + x] = floor_col;
			x++;
		}
		y++;
	}
}

void	draw_wall(t_game *game)
{
	game->raycast.line_height = (int)(WIN_HEIGHT / game->raycast.perp_dist);
	game->raycast.draw_start = -(game->raycast.line_height) / 2 + WIN_HEIGHT
		/ 2;
	if (game->raycast.draw_start < 0)
		game->raycast.draw_start = 0;
	game->raycast.draw_end = game->raycast.line_height / 2 + WIN_HEIGHT / 2;
	if (game->raycast.draw_end >= WIN_HEIGHT)
		game->raycast.draw_end = WIN_HEIGHT - 1;
}

void	set_wall_pixel(t_game *game)
{
	if (game->raycast.side == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.perp_dist
			* game->raycast.raydir_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.perp_dist
			* game->raycast.raydir_x;
	game->raycast.wall_x -= floor((game->raycast.wall_x));
}
