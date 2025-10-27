/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:16:34 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/27 19:32:02 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_side_dist_delta_init(t_game *game, t_ray *r)
{
	if (r->raydir_x < 0.0)
	{
		r->step_x = -1;
		r->side_distx = (game->player.pos_x - r->map_x) * r->delta_distx;
	}
	else
	{
		r->step_x = 1;
		r->side_distx = (r->map_x + 1.0 - game->player.pos_x) * r->delta_distx;
	}
	if (r->raydir_y < 0.0)
	{
		r->step_y = -1;
		r->side_disty = (game->player.pos_y - r->map_y) * r->delta_disty;
	}
	else
	{
		r->step_y = 1;
		r->side_disty = (r->map_y + 1.0 - game->player.pos_y) * r->delta_disty;
	}
}

// void	dda_init_ray(t_game *game, t_ray *r, int screen_x)
// {
// 	double	camera_x;

// 	camera_x = 2.0 * screen_x / (double)WIN_WIDTH - 1.0;
// 	r->camera_x = camera_x;
// 	r->raydir_x = game->player.dir_x + game->player.plane_x * camera_x;
// 	r->raydir_y = game->player.dir_y + game->player.plane_y * camera_x;
// 	r->map_x = (int)game->player.pos_x;
// 	r->map_y = (int)game->player.pos_y;
// 	dda_iter_limit(game, r);
// 	r->delta_distx = fabs(1.0 / r->raydir_x);
// 	r->delta_disty = fabs(1.0 / r->raydir_y);
// 	dda_side_dist_delta_init(game, r);
// 	r->hit = 0;
// 	r->side = 0;
// }
// appeller avec la colonne horizontale de pixel screen-x
int	ft_dda(t_game *game, t_ray *r, int screen_x)
{
	int		iter;
	char	cell;

	dda_init_ray(game, r, screen_x);
	iter = 0;
	while (!r->hit && iter++ < r->iter_limit)
	{
		dda_side_dist_delta_calc(r, iter);
		if (r->map_x < 0 || r->map_x >= game->map_width || r->map_y < 0
			|| r->map_y >= game->map_height)
		{
			r->hit = 1;
			return (0);
		}
		cell = get_char_at(game, r->map_y, r->map_x);
		if (cell == '1' || cell == ' ')
			r->hit = 1;
	}
	return (0);
}
