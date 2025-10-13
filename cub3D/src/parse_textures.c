/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:42:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/13 14:36:40 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	store_texture(t_game *game, char *path, e_texture tex_type)
{
	char	*dup;

	dup = ft_strdup(path);
	if (!dup)
		error_exit("Memory allocation failed", game);
	if (tex_type == NORTH)
	{
		game->tex_north = dup;
		game->has_tex_no = 1;
	}
	else if (tex_type == SOUTH)
	{
		game->tex_south = dup;
		game->has_tex_so = 1;
	}
	else if (tex_type == WEST)
	{
		game->tex_west = dup;
		game->has_tex_we = 1;
	}
	else if (tex_type == EAST)
	{
		game->tex_east = dup;
		game->has_tex_ea = 1;
	}
}

static int	identify_texture(char *id, t_game *game)
{
	if (ft_strncmp(id, "NO ", 3) == 0 && !game->has_tex_no)
		return (NORTH);
	else if (ft_strncmp(id, "SO ", 3) == 0 && !game->has_tex_so)
		return (SOUTH);
	else if (ft_strncmp(id, "WE ", 3) == 0 && !game->has_tex_we)
		return (WEST);
	else if (ft_strncmp(id, "EA ", 3) == 0 && !game->has_tex_ea)
		return (EAST);
	return (-1);
}

static int	parse_texture_identifier(char *line, t_game *game)
{
	char	*id;
	char	*path;
	int		tex_type;

	id = skip_spaces(line);
	tex_type = identify_texture(id, game);
	if (tex_type == -1)
		return (0);
	path = skip_spaces(id + 2);
	trim_end(path);
	if (ft_strlen(path) == 0)
		error_exit("Empty texture path", game);
	store_texture(game, path, tex_type);
	return (1);
}

int	parse_textures(t_game *game, int fd)
{
	char	*line;
	int		found;

	found = 0;
	while (found < 4)
	{
		line = get_next_line(fd);
		if (!line)
			error_exit("Unexpected EOF while parsing textures", game);

		if (ft_strlen(line) == 0 || line[0] == '\n')
		{
			free(line);
			continue;
		}
		if (parse_texture_identifier(line, game))
			found++;
		else
		{
			free(line);
			break;
		}
		free(line);
	}

	return (1);
}
