/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:03:45 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/13 14:53:55 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**split_rgb(char *rgb_str, t_game *game)
{
	char	**split;
	int		i;

	split = ft_split(rgb_str, ',');
	if (!split || !split[0] || !split[1] || !split[2] || split[3])
	{
		if (split)
		{
			i = 0;
			while (split[i])
				free(split[i++]);
			free(split);
		}
		error_exit("Invalid RGB format (expected R,G,B)", game);
	}
	return (split);
}

static int	parse_rgb(char *rgb_str, t_color *color, t_game *game)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = split_rgb(rgb_str, game);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		error_exit("RGB values must be in range [0,255]", game);
	color->r = r;
	color->g = g;
	color->b = b;
	return (1);
}

static int	parse_color_identifier(char *line, t_game *game)
{
	char	*id;
	char	*rgb_str;
	t_color	*target;
	int		*flag;

	id = skip_spaces(line);
	if (ft_strncmp(id, "F ", 2) == 0 && !game->has_floor_color)
	{
		target = &game->floor_color;
		flag = &game->has_floor_color;
	}
	else if (ft_strncmp(id, "C ", 2) == 0 && !game->has_ceiling_color)
	{
		target = &game->ceiling_color;
		flag = &game->has_ceiling_color;
	}
	else
		return (0);
	rgb_str = skip_spaces(id + 1);
	trim_end(rgb_str);
	if (ft_strlen(rgb_str) == 0)
		error_exit("Empty color value", game);
	parse_rgb(rgb_str, target, game);
	*flag = 1;
	return (1);
}

int	parse_colors(t_game *game, int fd)
{
	char	*line;
	int		found;

	found = 0;
	while (found < 2)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit("Unexpected EOF while parsing colors", game);
		if (ft_strlen(line) == 0 || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (parse_color_identifier(line, game))
			found++;
		else
		{
			free(line);
			break ;
		}
		free(line);
	}
	return (1);
}
