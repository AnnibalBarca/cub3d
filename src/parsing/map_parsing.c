/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 12:50:31 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/23 15:46:36 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_strappend(char *s1, char *s2)
{
	char	*str;

	if (!s1 || !s2)
		return (NULL);
	str = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!str)
	{
		free(s1);
		free(s2);
		return (NULL);
	}
	ft_strlcpy(str, s1, ft_strlen(s1) + 1);
	ft_strlcat(str, s2, ft_strlen(s1) + ft_strlen(s2) + 1);
	free(s1);
	free(s2);
	return (str);
}

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

static char	*read_map_content(t_game *game, int fd)
{
	char	*line;
	char	*tmp;

	tmp = ft_strdup("");
	if (!tmp)
	{
		ft_putstr_fd("Failed to allocate memory", 2);
		return (NULL);
	}
	while (1)
	{
		errno = 0;
		line = get_next_line(fd);
		if (!line)
			break ;
// fix pour eviter les sauts de ligne dans la map
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
		print_e("Failed to read map file", 0);
	}
	game->map = ft_split(tmp, '\n');
	free(tmp);
	if (!game->map)
		return (0);
	if (!validate_map(game))
		return (0);
	return (1);
}
