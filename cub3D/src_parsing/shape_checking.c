#include "cub3d.h"

int	is_player(char c)
{
	if (c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	is_map_char(char c)
{
	if (c == '0' || c == '1' || c == '\n' || c == ' ')
		return (1);
	return (0);
}
int	is_filled_char(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'E' || c == 'S' || c == 'W')
		return (1);
	return (0);
}

int	surrounding_is_filled(int col, int row, t_game *game)
{
	if (col == 0 || row == 0 || col == game->map_height
		|| col == game->map_width)
		return (0);
	if (col != 0)
		if (!is_filled_char(game->map[col - 1][row]))
			return (0);
	if (row != 0)
		if (!is_filled_char(game->map[col][row - 1]))
			return (0);
	if (col != game->map_height)
		if (!is_filled_char(game->map[col + 1][row]))
			return (0);
	if (row != game->map_width)
		if (!is_filled_char(game->map[col - 1][row]))
			return (0);
	return (1);
}

int	walled_checker(t_game *game)
{
	int	col;
	int	row;

	col = 0;
	while (col < game->map_width)
	{
		row = 0;
		while (row < game->map_height)
		{
			if (game->map[col][row] == '0' || is_player(game->map[col][row]))
			{
				if (!surrounding_is_filled(col, row, game))
					return (0);
			}
			row++;
		}
		col++;
	}
	return (1);
}

int	char_checker(t_game *game)
{
	int	col;
	int	row;
	int	pcount;

	col = 0;
	pcount = 0;
	while (col < game->map_width)
	{
		row = 0;
		while (row < game->map_height)
		{
			if (game->map[col][row] == '0')
			{
				if ((is_player(game->map[col][row])))
				{
					pcount++;
					if (pcount > 1)
						return (0);
				}
				else if (!is_map_char(game->map[col][row]))
					return (0);
			}
			row++;
		}
		col++;
	}
	return (1);
}
