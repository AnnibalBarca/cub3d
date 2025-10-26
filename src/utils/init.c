/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 10:01:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/26 16:29:50 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cub3d.h"

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

void	init_textures(t_game *game)
{
	init_img(&game->textures[0]);
	init_img(&game->textures[1]);
	init_img(&game->textures[2]);
	init_img(&game->textures[3]);
	game->has_tex_no = 0;
	game->has_tex_so = 0;
	game->has_tex_we = 0;
	game->has_tex_ea = 0;
	game->path_north = NULL;
	game->path_south = NULL;
	game->path_east = NULL;
	game->path_west = NULL;
}

void	init_game(t_game *game)
{
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
	game->has_floor_color = 0;
	game->has_ceiling_color = 0;
	game->key.go_backward = 0;
	game->key.go_forward = 0;
	game->key.go_left = 0;
	game->key.go_right = 0;
	game->key.turn_left = 0;
	game->key.turn_right = 0;
	game->last_time = 0;
	game->delta_time = 0;
	game->screen_height = WIN_HEIGHT;
	game->screen_width = WIN_WIDTH;
	init_img(&game->data.img);
	init_textures(game);
}

void	set_vector(t_player *player)
{
	if (player->player_letter == 'N')
	{
		player->dir_x = 0;
		player->dir_y = -1;

	}
	else if (player->player_letter == 'S')
	{
		player->dir_x = 0;
		player->dir_y = 1;
	}
	else if (player->player_letter == 'E')
	{
		player->dir_x = 1;
		player->dir_y = 0;

	}
	else if (player->player_letter == 'W')
	{
		player->dir_x = -1;
		player->dir_y = 0;
	}
}

void	set_camera(t_player *player)
{
	if (player->player_letter == 'N')
	{
		player->plane_x = 0.66;
		player->plane_y = 0;
	}
	if (player->player_letter == 'S')
	{
		player->plane_x = -0.66;
		player->plane_y = 0;
	}
	if (player->player_letter == 'E')
	{
		player->plane_x = 0;
		player->plane_y = 0.66;
	}
	if (player->player_letter == 'W')
	{
		player->plane_x = 0;
		player->plane_y = -0.66;
	}
}

void init_mmap(t_game *game)
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