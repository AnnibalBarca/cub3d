/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:03:45 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/18 15:26:37 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	**split_rgb(char *rgb_str)
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
		ft_putstr_fd("Invalid RGB format (expected R,G,B)\n", 0);
		split = NULL;
	}
	return (split);
}

static int	parse_rgb(char *rgb_str, t_color *color)
{
	char	**split;
	int		r;
	int		g;
	int		b;

	split = split_rgb(rgb_str);
	if (!split)
		return (0);
	r = ft_atoi(split[0]);
	g = ft_atoi(split[1]);
	b = ft_atoi(split[2]);
	free(split[0]);
	free(split[1]);
	free(split[2]);
	free(split);
	if (r < 0 || r > 255 || g < 0 || g > 255 || b < 0 || b > 255)
		return (print_e("RGB values must be in range [0,255]\n", 0));
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

	id = skip_spaces(line);
	if (ft_strncmp(id, "F ", 2) == 0 && !game->has_floor_color)
		target = &game->floor_color;
	else if (ft_strncmp(id, "C ", 2) == 0 && !game->has_ceiling_color)
		target = &game->ceiling_color;
	else
		return (0);
	rgb_str = skip_spaces(id + 1);
	trim_end(rgb_str);
	if (ft_strlen(rgb_str) == 0)
		return (print_e("Empty color value\n", -1));
	if (!parse_rgb(rgb_str, target))
		return (0);
	if (*id == 'F')
		game->has_floor_color = 1;
	else
		game->has_ceiling_color = 1;
	return (1);
}

static int	handle_color_line(char *line, t_game *game, int *found)
{
	int	error;

	if (ft_strlen(line) == 0 || line[0] == '\n')
	{
		free(line);
		return (1);
	}
	error = parse_color_identifier(line, game);
	if (error == 1)
	{
		(*found)++;
		free(line);
		return (1);
	}
	if (error == 0)
	{
		free(line);
		return (0);
	}
	free(line);
	return (2);
}

int	parse_colors(t_game *game, int fd)
{
	char	*line;
	int		found;
	int		ret;

	found = 0;
	while (found < 2)
	{
		line = get_next_line(fd);
		if (!line)
			return (print_e("Unexpected EOF while parsing colors\n", 0));
		ret = handle_color_line(line, game, &found);
		if (ret == 0)
			return (0);
		if (ret == 2)
			break ;
	}
	return (1);
}
