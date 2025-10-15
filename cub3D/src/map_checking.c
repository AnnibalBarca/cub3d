/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checking.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:02:57 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/15 13:36:11 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
		game->player.dir = c;
	}
	return (1);
}

int	char_checker(t_game *game, char c)
{
	int		row;
	int		col;
	int		pcount;

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
