/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda_helpers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 13:25:10 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/27 14:50:01 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void ft_iter_limit(t_game *game, t_ray *r)
{
    r->iter_limit = (game->map_width + game->map_height) * 4;
    if (r->iter_limit < 1024)
        r->iter_limit = 1024;
}

void    compute_perp_distance(t_game *game, t_ray *r)
{
    double perp;

    if (r->side == 0)
        perp = (r->map_x - game->player.pos_x + (1 - r->step_x) / 2.0)
            / (r->raydir_x == 0.0 ? 1e-30 : r->raydir_x);
    else
        perp = (r->map_y - game->player.pos_y + (1 - r->step_y) / 2.0)
            / (r->raydir_y == 0.0 ? 1e-30 : r->raydir_y);
    if (!(perp > 0.0))
        perp = 1e-6;
    r->perp_dist = perp;
}