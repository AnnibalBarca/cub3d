/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:50:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/09 18:41:43 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	tab_len(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

int	validate_map(t_game *game)
{
	char	c;

	c = 'c';
	if (!walled_checker(game))
		return (print_e("Map layout is incorrect\n", 0));
	if (!char_checker(game, c))
		return (print_e("Map contains wrong characters\n", 0));
	return (1);
}

static char	*read_content(t_game *game, char *tmp, int fd)
{
	char	*line;

	while (1)
	{
		errno = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
		if (ft_strlen(line) <= 1 && game->map_height > 0)
		{
			free(line);
			free(tmp);
			return (NULL);
		}
		if ((int)ft_strlen(line) > game->map_width)
			game->map_width = ft_strlen(line) - 1;
		if (ft_strlen(line) > 1)
			game->map_height++;
		tmp = ft_strappend(tmp, line);
		if (!tmp)
			break ;
	}
	return (tmp);
}

static char	*read_map_content(t_game *game, int fd)
{
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
	{
		ft_putstr_fd("Failed to allocate memory\n", 2);
		return (NULL);
	}
	return (read_content(game, tmp, fd));
}

int	parse_map(t_game *game, int fd)
{
	char	*tmp;

	tmp = read_map_content(game, fd);
	if (!tmp)
		return (0);
	if (errno)
	{
		if (tmp)
			free(tmp);
		print_e("Failed to read map file\n", 0);
	}
	game->map = ft_split(tmp, '\n');
	free(tmp);
	if (!game->map)
		return (0);
	if (!validate_map(game))
		return (0);
	return (1);
}
