/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:04:26 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/23 15:33:57 by almeekel         ###   ########.fr       */
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
	if (!game || !game->has_tex_ea || !game->has_tex_no || !game->has_tex_so || !game->has_tex_we)
		return (print_e("NULL game or incomplete textures\n", 1));
	if (load_texture(game, &game->textures[0], game->path_north))
		return (print_e("Failed to load North text.\n", 1));
	if (load_texture(game, &game->textures[1], game->path_south))
		return (print_e("Failed to load South text.\n", 1));
	if (load_texture(game, &game->textures[2], game->path_west))
		return (print_e("Failed to load West text.\n", 1));
	if (load_texture(game, &game->textures[3], game->path_east))
		return (print_e("Failed to load East text\n", 1));
	return (0);
}
