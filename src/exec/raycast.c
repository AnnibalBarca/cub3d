/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:41:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/28 16:59:26 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_init_ray(t_game *game, t_ray *r, int screen_x)
{
	double	camera_x;

	camera_x = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	r->raydir_x = game->player.dir_x + game->player.plane_x * camera_x;
	r->raydir_y = game->player.dir_y + game->player.plane_y * camera_x;
	r->map_x = (int)game->player.pos_x;
	r->map_y = (int)game->player.pos_y;
	dda_iter_limit(game, r);
	r->delta_distx = fabs(1.0 / r->raydir_x);
	r->delta_disty = fabs(1.0 / r->raydir_y);
	dda_side_dist_delta_init(game, r);
	r->hit = 0;
	r->side = 0;
}
static void	calc_line_height(t_game *game, t_ray *r)
{
	if (r->side == 0)
		r->perp_dist = (r->side_distx - r->delta_distx);
	else
		r->perp_dist = (r->side_disty - r->delta_disty);
	r->line_height = (int)(game->screen_height / r->perp_dist);
	r->draw_start = -r->line_height / 2 + game->screen_height / 2;
	if (r->draw_start < 0)
		r->draw_start = 0;
	r->draw_end = r->line_height / 2 + game->screen_height / 2;
	if (r->draw_end >= game->screen_height)
		r->draw_end = game->screen_height - 1;
	if (r->side == 0)
		r->wall_x = game->player.pos_y + r->perp_dist * r->raydir_y;
	else
		r->wall_x = game->player.pos_x + r->perp_dist * r->raydir_x;
	r->wall_x -= floor(r->wall_x);
}

int	raycasting(t_game *game)
{
	t_ray	*r;
	int		x;

	x = 0;
	while (x < WIN_WIDTH)
	{
		dda_init_ray(game, &r, x);
		ft_dda(game, &r, x);
		calc_line_height(game, &r);
		// update_texture_pixels(game, &r, x);
		x++;
	}
	return (0);
}
