/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:02:57 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/15 14:24:34 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	set_player_direction(t_game *game, char dir_char)
{
	if (dir_char == 'N')
	{
		game->player.dir = 3 * M_PI / 2;
		game->player.plane_x = 0.66;
		game->player.plane_y = 0;
	}
	else if (dir_char == 'S')
	{
		game->player.dir = M_PI / 2;
		game->player.plane_x = -0.66;
		game->player.plane_y = 0;
	}
	else if (dir_char == 'E')
	{
		game->player.dir = 0;
		game->player.plane_x = 0;
		game->player.plane_y = 0.66;
	}
	else if (dir_char == 'W')
	{
		game->player.dir = M_PI;
		game->player.plane_x = 0;
		game->player.plane_y = -0.66;
	}
}

int	walled_checker(t_game *game)
{
	int		row;
	int		col;
	char	c;

	if (!game || !game->map)
		return (0);
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			c = get_char_at(game, row, col);
			if (c == '0' || is_player(c))
			{
				if (!surrounding_is_filled(row, col, game))
					return (0);
			}
			col++;
		}
		row++;
	}
	return (1);
}

static int	check_and_set_player(t_game *game, int row, int col, int *pcount)
{
	char	c;

	c = get_char_at(game, row, col);
	if (is_player(c))
	{
		(*pcount)++;
		if (*pcount > 1)
			return (0);
		game->player.x = (float)col + 0.5f;
		game->player.y = (float)row + 0.5f;
		set_player_direction(game, c);
	}
	return (1);
}

int	char_checker(t_game *game, char c)
{
	int	row;
	int	col;
	int	pcount;

	if (!game || !game->map)
		return (0);
	pcount = 0;
	row = 0;
	while (row < game->map_height)
	{
		col = 0;
		while (col < game->map_width)
		{
			c = get_char_at(game, row, col);
			if (!is_map_char(c))
				return (0);
			if (!check_and_set_player(game, row, col, &pcount))
				return (0);
			col++;
		}
		row++;
	}
	if (pcount != 1)
		return (0);
	return (1);
}
