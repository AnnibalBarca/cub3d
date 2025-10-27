/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:16:34 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/27 14:50:50 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int ft_dda(t_game *game, t_ray *ray)
{
    int iter;

    iter = 0
    while (!ray->hit && iter++ < iter_limit)
    {
        if (ray->side_distx < ray->side_disty)
        {
            ray->side_distx += ray->delta_distx;
            ray->map_x += ray->step_x;
            ray->side = 0;
        }
        else
        {
            ray->side_disty += ray->delta_disty;
            ray->map_y += ray->step_y;
            ray->side = 1;
        }
        
    }
}