/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:41:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/29 19:06:38 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_init_ray(t_game *game, int screen_x)
{
	double	camera_x;

	camera_x = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	game->raycast.raydir_x = game->player.dir_x + game->player.plane_x
		* camera_x;
	game->raycast.raydir_y = game->player.dir_y + game->player.plane_y
		* camera_x;
	game->raycast.map_x = (int)game->player.pos_x;
	game->raycast.map_y = (int)game->player.pos_y;
	dda_iter_limit(game);
	game->raycast.delta_distx = fabs(1.0 / game->raycast.raydir_x);
	game->raycast.delta_disty = fabs(1.0 / game->raycast.raydir_y);
	dda_side_dist_delta_init(game);
	game->raycast.hit = 0;
	game->raycast.side = 0;
}
static void	calc_line_height(t_game *game)
{
	t_img	*texture;

	if (game->raycast.side == 0)
		game->raycast.perp_dist = (game->raycast.side_distx
				- game->raycast.delta_distx);
	else
		game->raycast.perp_dist = (game->raycast.side_disty
				- game->raycast.delta_disty);
	game->raycast.line_height = (int)(game->screen_height
			/ game->raycast.perp_dist);
	game->raycast.draw_start = -game->raycast.line_height / 2
		+ game->screen_height / 2;
	if (game->raycast.draw_start < 0)
		game->raycast.draw_start = 0;
	game->raycast.draw_end = game->raycast.line_height / 2 + game->screen_height
		/ 2;
	if (game->raycast.draw_end >= game->screen_height)
		game->raycast.draw_end = game->screen_height - 1;
	if (game->raycast.side == 0)
		game->raycast.wall_x = game->player.pos_y + game->raycast.perp_dist
			* game->raycast.raydir_y;
	else
		game->raycast.wall_x = game->player.pos_x + game->raycast.perp_dist
			* game->raycast.raydir_x;
	game->raycast.wall_x -= floor(game->raycast.wall_x);
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

int	raycasting(t_game *game)
{
	int	x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		dda_init_ray(game, x);
		ft_dda(game);
		calc_line_height(game);
		draw_texture(game, x);
		x++;
	}
	return (0);
}
