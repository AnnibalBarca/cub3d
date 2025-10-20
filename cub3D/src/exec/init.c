/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:01:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/20 10:30:00 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_img(t_img *img)
{
	img->mlx_img = NULL;
	img->addr = NULL;
	img->bpp = 0;
	img->line_len = 0;
	img->endian = -1;
	img->w = 0;
	img->h = 0;
}

void	init_game(t_game *game)
{
	init_img(&game->textures[0]);
	init_img(&game->textures[1]);
	init_img(&game->textures[2]);
	init_img(&game->textures[3]);
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->floor_color.r = -1;
	game->floor_color.g = -1;
	game->floor_color.b = -1;
	game->ceiling_color.r = -1;
	game->ceiling_color.g = -1;
	game->ceiling_color.b = -1;
	game->player.pos_x = -1.0f;
	game->player.pos_y = -1.0f;
	game->player.dir_x = 0;
	game->player.dir_y = 0;
	game->has_tex_no = 0;
	game->has_tex_so = 0;
	game->has_tex_we = 0;
	game->has_tex_ea = 0;
	game->has_floor_color = 0;
	game->has_ceiling_color = 0;
	game->screen_width = 0;
	game->screen_height = 0;
	game->key.go_backward = 0;
	game->key.go_forward = 0;
	game->key.go_left = 0;
	game->key.go_right = 0;
	game->key.turn_left = 0;
	game->key.turn_right = 0;
}