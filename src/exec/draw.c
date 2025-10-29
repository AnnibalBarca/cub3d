/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:33:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/29 19:06:46 by nagaudey         ###   ########.fr       */
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

void	draw_floor(t_game *game)
{
	int				x;
	int				y;
	unsigned int	ceiling;
	unsigned int	floor_col;
	unsigned int	*pixels;

	ceiling = t_color_to_int(game->ceiling_color);
	floor_col = t_color_to_int(game->floor_color);
	pixels = (unsigned int *)game->data.img.addr;
	y = 0;
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

void	set_texture(t_game *game)
{
	t_img	*texture;

	texture = get_texture(game);
	if (!texture)
		return ;
	game->raycast.tex_x = (int)(game->raycast.wall_x * texture->w);
	if (game->raycast.side == 0 && game->raycast.raydir_x > 0)
		game->raycast.tex_x = texture->w - game->raycast.tex_x - 1;
	if (game->raycast.side == 1 && game->raycast.raydir_y < 0)
		game->raycast.tex_x = texture->w - game->raycast.tex_x - 1;
	if (game->raycast.tex_x < 0)
		game->raycast.tex_x = 0;
	if (game->raycast.tex_x >= texture->w)
		game->raycast.tex_x = texture->w - 1;
}

void	draw_texture(t_game *game, int x)
{
	t_img			*texture;
	double			step;
	double			texture_pos;
	unsigned int	color;
	int				y;

	texture = get_texture(game);
	if (!texture || !texture->addr || !texture->mlx_img)
		return ;
	step = 1.0 * (double)texture->h / (double)game->raycast.line_height;
	texture_pos = (game->raycast.draw_start - (WIN_HEIGHT / 2)
			+ game->raycast.line_height / 2) * step;
	y = game->raycast.draw_start;
	while (y < game->raycast.draw_end)
	{
		game->raycast.tex_y = (int)(texture_pos) & (texture->h - 1);
		color = *(unsigned int *)(texture->addr + (game->raycast.tex_y
					* texture->line_len + game->raycast.tex_x * (texture->bpp
						/ 8)));
		put_pixel(game, x, y, color);
		texture_pos += step;
		y++;
	}
}
