/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_char_checking.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 11:00:13 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/13 15:40:19 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || is_player(c) || c == ' ')
		return (1);
	return (0);
}

int	is_filled_char(char c)
{
	if (c == '0' || c == '1' || is_player(c))
		return (1);
	return (0);
}

char	get_char_at(t_game *game, int row, int col)
{
	int	rowlen;

	if (row < 0 || row >= game->map_height || col < 0)
		return (' ');
	rowlen = (int)ft_strlen(game->map[row]);
	if (col >= rowlen)
		return (' ');
	return (game->map[row][col]);
}

int	surrounding_is_filled(int row, int col, t_game *game)
{
	if (row == 0 || row == game->map_height - 1)
		return (0);
	if (col == 0 || col >= game->map_width - 1)
		return (0);
	if (!is_filled_char(get_char_at(game, row - 1, col)))
		return (0);
	if (!is_filled_char(get_char_at(game, row + 1, col)))
		return (0);
	if (!is_filled_char(get_char_at(game, row, col - 1)))
		return (0);
	if (!is_filled_char(get_char_at(game, row, col + 1)))
		return (0);
	return (1);
}
