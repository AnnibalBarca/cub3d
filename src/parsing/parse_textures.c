/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_textures.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 13:42:48 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/19 16:37:51 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	attribute_texture(t_game *game, char *dup, t_texture tex_type)
{
	if (tex_type == NORTH)
	{
		game->path_north = dup;
		game->has_tex_no = 1;
	}
	else if (tex_type == SOUTH)
	{
		game->path_south = dup;
		game->has_tex_so = 1;
	}
	else if (tex_type == WEST)
	{
		game->path_west = dup;
		game->has_tex_we = 1;
	}
	else if (tex_type == EAST)
	{
		game->path_east = dup;
		game->has_tex_ea = 1;
	}
}

static int	store_texture(t_game *game, char *path, t_texture tex_type)
{
	char	*dup;
	int		fd;

	fd = open(path, O_RDONLY);
	if (fd < 0)
		return (print_e("Texture file does not exist or cannot be opened\n",
				0));
	dup = ft_strdup(path);
	if (!dup)
		return (print_e("Memory allocation failed\n", 0));
	attribute_texture(game, dup, tex_type);
	close(fd);
	return (1);
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
		return (print_e("Empty texture path\n", 0));
	if (!store_texture(game, path, tex_type))
		return (0);
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
			return (print_e("Unexpected EOF while parsing textures\n", 0));
		if (ft_strlen(line) == 0 || line[0] == '\n')
		{
			free(line);
			continue ;
		}
		if (parse_texture_identifier(line, game))
			found++;
		else
		{
			free(line);
			return (print_e("Uncorrect required texture elements"
					"(NO/SO/WE/EA)\n", 0));
		}
		free(line);
	}
	return (1);
}
