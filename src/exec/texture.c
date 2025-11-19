/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:04:26 by nagaudey          #+#    #+#             */
/*   Updated: 2025/11/19 16:42:00 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	load_texture(t_data *data, t_img *tex_img, char *path)
{
	if (!path || !data || !tex_img)
		return (print_e("NULL parameter in load_texture\n", 1));
	tex_img->w = 0;
	tex_img->h = 0;
	tex_img->mlx_img = mlx_xpm_file_to_image(data->mlx_ptr, path, &tex_img->w,
			&tex_img->h);
	if (!tex_img->mlx_img)
		return (1);
	tex_img->addr = mlx_get_data_addr(tex_img->mlx_img, &tex_img->bpp,
			&tex_img->line_len, &tex_img->endian);
	if (!tex_img->addr)
	{
		mlx_destroy_image(data->mlx_ptr, tex_img->mlx_img);
		return (print_e("Failed to get texture address\n", 1));
	}
	return (0);
}

int	load_textures(t_game *game)
{
	if (!game || !game->has_tex_ea || !game->has_tex_no || !game->has_tex_so
		|| !game->has_tex_we)
		return (print_e("NULL game or incomplete textures\n", 1));
	if (load_texture(&game->data, &game->textures[NORTH], game->path_north))
		return (print_e("Failed to load North text.\n", 1));
	if (load_texture(&game->data, &game->textures[SOUTH], game->path_south))
		return (print_e("Failed to load South text.\n", 1));
	if (load_texture(&game->data, &game->textures[WEST], game->path_west))
		return (print_e("Failed to load West text.\n", 1));
	if (load_texture(&game->data, &game->textures[EAST], game->path_east))
		return (print_e("Failed to load East text\n", 1));
	return (0);
}

t_img	*get_texture(t_game *game)
{
	if (game->raycast.side == 0)
	{
		if (game->raycast.raydir_x > 0)
			return (&game->textures[WEST]);
		else
			return (&game->textures[EAST]);
	}
	else
	{
		if (game->raycast.raydir_y > 0)
			return (&game->textures[NORTH]);
		else
			return (&game->textures[SOUTH]);
	}
	return (NULL);
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
