/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:25:10 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/27 16:36:05 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_iter_limit(t_game *game, t_ray *r)
{
	r->iter_limit = (game->map_width + game->map_height) * 4;
	if (r->iter_limit < 1024)
		r->iter_limit = 1024;
}

void	dda_compute_perp_distance(t_game *game, t_ray *r)
{
    double dx, dy;

    if (r->side == 0)
        dx = r->map_x - game->player.pos_x + (1 - r->step_x) / 2.0;
    else
        dx = r->map_x - game->player.pos_x + 0.5;

    if (r->side == 1)
        dy = r->map_y - game->player.pos_y + (1 - r->step_y) / 2.0;
    else
        dy = r->map_y - game->player.pos_y + 0.5;
    r->perp_dist = sqrt(dx * dx + dy * dy) * 
                   fabs(r->raydir_x * dx + r->raydir_y * dy) / 
                   sqrt(r->raydir_x * r->raydir_x + r->raydir_y * r->raydir_y);
    if (r->perp_dist <= 0.0)
        r->perp_dist = 0.1;
}

void	dda_side_dist_delta_calc(t_ray *r, int iter)
{
	if (r->side_distx < r->side_disty)
	{
		r->side_distx += r->delta_distx;
		r->map_x += r->step_x;
		r->side = 0;
	}
	else
	{
		r->side_disty += r->delta_disty;
		r->map_y += r->step_y;
		r->side = 1;
	}
}
int	dda_register_hit(t_ray *r)
{
	r->hit = 1;
	return (0);
}