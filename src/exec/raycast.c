/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 13:41:50 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/27 18:30:41 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_init_ray(t_game *game, t_ray *r, int screen_x)
{
    double	camera_x;

	camera_x = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
	r->camera_x = camera_x;
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

int raycasting(t_game *game)
{
    t_ray   *r;
    int x;

    
    while (x < WIN_WIDTH)
    {
        dda_init_ray(game, r, x);
        ft_dda();
        calc_line_height();
        // update_texture_pixels;
        x++;
    }
    
}