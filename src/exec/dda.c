/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:16:34 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/28 16:59:52 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	dda_iter_limit(t_game *game, t_ray *r)
{
	r->iter_limit = (game->map_width + game->map_height) * 4;
	if (r->iter_limit < 1024)
		r->iter_limit = 1024;
}

static void	dda_side_dist_delta_calc(t_ray *r, int iter)
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
static void	dda_side_dist_delta_init(t_game *game, t_ray *r)
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

int	ft_dda(t_game *game, t_ray *r, int screen_x)
{
	int		iter;
	char	cell;

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
