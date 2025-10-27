/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 20:47:39 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/27 17:47:42 by nagaudey         ###   ########.fr       */
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

void	draw_one_minimap_cell(t_game *game, int x, int y)
{
	int	color;
	int	pixel_x;
	int	pixel_y;
	int	map_x;
	int	map_y;

	map_x = (int)(game->player.pos_x + x / (float)game->mmap.scale);
	map_y = (int)(game->player.pos_y + y / (float)game->mmap.scale);
	pixel_x = game->mmap.cx + x;
	pixel_y = game->mmap.cy + y;
	if (x * x + y * y > MINIMAP_RADIUS * MINIMAP_RADIUS)
		return ;
	if (pixel_x < 0 || pixel_x >= game->screen_width || pixel_y < 0
		|| pixel_y >= game->screen_height)
		return ;
	if (map_y < 0 || map_y >= game->map_height || map_x < 0
		|| map_x >= game->map_width)
	{
		put_pixel(game, pixel_x, pixel_y, 0x000000);
		return ;
	}
	if (game->map[map_y][map_x])
		color = get_minimap_cell_color(game, game->map[map_y][map_x]);
	else
		color = 0x000000;
	put_pixel(game, pixel_x, pixel_y, color);
}

void	draw_minimap_player(t_game *game)
{
	int	dx;
	int	dy;
	int	pixel_x;
	int	pixel_y;

	dy = -3;
	while (dy <= 3)
	{
		dx = -3;
		while (dx <= 3)
		{
			if (dx * dx + dy * dy <= 9)
			{
				pixel_x = game->mmap.cx + dx;
				pixel_y = game->mmap.cy + dy;
				if (pixel_x >= 0 && pixel_x < game->screen_width && pixel_y >= 0
					&& pixel_y < game->screen_height)
				{
					put_pixel(game, pixel_x, pixel_y, 0xFF0000);
				}
			}
			dx++;
		}
		dy++;
	}
}

void	draw_minimap_cells(t_game *game)
{
	int	x;
	int	y;
	int	r;

	r = MINIMAP_RADIUS;
	y = -r;
	while (y <= r)
	{
		x = -r;
		while (x <= r)
		{
			draw_one_minimap_cell(game, x, y);
			x++;
		}
		y++;
	}
}

void	draw_minimap_direction(t_game *game)
{
    int		i;
    int		line_length;
    int		pixel_x;
    int		pixel_y;

    line_length = 15;
    i = 0;
    while (i < line_length)
    {
        pixel_x = game->mmap.cx + (int)(game->player.dir_x * i);
        pixel_y = game->mmap.cy + (int)(game->player.dir_y * i);
        if (pixel_x >= 0 && pixel_x < game->screen_width
            && pixel_y >= 0 && pixel_y < game->screen_height)
        {
            put_pixel(game, pixel_x, pixel_y, 0xFFFF00);
        }
        i++;
    }
}

void	draw_minimap(t_game *game)
{
    draw_minimap_cells(game);
    draw_minimap_direction(game);
    draw_minimap_player(game);
}

void	draw_minimap_compass(t_game *game)
{
	int cx;
	int cy;
	int r;

	cx = game->mmap.cx;
	cy = game->mmap.cy;
	r = MINIMAP_RADIUS + 12;
	mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, cx, cy - r, 0xFFFFFF,
		"N");
	mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, cx, cy + r, 0xFFFFFF,
		"S");
	mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, cx - r, cy, 0xFFFFFF,
		"W");
	mlx_string_put(game->data.mlx_ptr, game->data.win_ptr, cx + r, cy, 0xFFFFFF,
		"E");
}