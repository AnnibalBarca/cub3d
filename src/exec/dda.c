/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/27 14:16:34 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/17 13:45:08 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	dda_loop_alg(t_ray *r)
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

void	dda_iter_limit(t_game *game)
{
	game->raycast.iter_limit = (game->map_width + game->map_height) * 4;
	if (game->raycast.iter_limit < 1024)
		game->raycast.iter_limit = 1024;
}

void	dda_side_dist_delta_calc(t_game *game)
{
	if (game->raycast.side_distx < game->raycast.side_disty)
	{
		game->raycast.side_distx += game->raycast.delta_distx;
		game->raycast.map_x += game->raycast.step_x;
		game->raycast.side = 0;
	}
	else
	{
		game->raycast.side_disty += game->raycast.delta_disty;
		game->raycast.map_y += game->raycast.step_y;
		game->raycast.side = 1;
	}
}

void	dda_side_dist_delta_init(t_game *game)
{
	t_ray	*r;

	r = &game->raycast;
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

int	ft_dda(t_game *game)
{
	int		iter;
	char	cell;
	t_ray	*r;

	r = &game->raycast;
	iter = 0;
	while (!r->hit && iter++ < r->iter_limit)
	{
		dda_loop_alg(r);
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
