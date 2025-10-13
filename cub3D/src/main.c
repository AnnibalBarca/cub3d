/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:02:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/13 15:45:03 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	init_game(t_game *game)
{
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
	game->tex_north = NULL;
	game->tex_south = NULL;
	game->tex_west = NULL;
	game->tex_east = NULL;
	game->floor_color.r = -1;
	game->floor_color.g = -1;
	game->floor_color.b = -1;
	game->ceiling_color.r = -1;
	game->ceiling_color.g = -1;
	game->ceiling_color.b = -1;
	game->player.x = -1.0f;
	game->player.y = -1.0f;
	game->player.dir = '\0';
	game->has_tex_no = 0;
	game->has_tex_so = 0;
	game->has_tex_we = 0;
	game->has_tex_ea = 0;
	game->has_floor_color = 0;
	game->has_ceiling_color = 0;
	game->screen_width = 0;
	game->screen_height = 0;
}

void	free_game(t_game *game)
{
	int	i;

	if (game->tex_north)
		free(game->tex_north);
	if (game->tex_south)
		free(game->tex_south);
	if (game->tex_west)
		free(game->tex_west);
	if (game->tex_east)
		free(game->tex_east);
	if (game->map)
	{
		i = 0;
		while (game->map[i])
		{
			free(game->map[i]);
			i++;
		}
		free(game->map);
	}
}

int	parse_cub_file(t_game *game, char *filename)
{
	int	fd;

	if (ft_strlen(filename) < 5 || ft_strncmp(&filename[ft_strlen(filename)
				- 4], ".cub", 4) != 0)
		error_exit("Invalid file extension (expected .cub)", game);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		error_exit("Failed to open file", game);
	if (!parse_textures(game, fd))
	{
		close(fd);
		return (0);
	}
	if (!parse_colors(game, fd))
	{
		close(fd);
		return (0);
	}
	if (!validate_required_elements(game))
	{
		close(fd);
		error_exit("Missing required elements (NO/SO/WE/EA/F/C)", game);
	}
	if (!parse_map(game, fd))
	{
		close(fd);
		return (0);
	}
	close(fd);
	return (1);
}

int	main(int argc, char **argv)
{
	t_game	game;

	if (argc != 2)
	{
		printf("Usage: %s <map.cub>\n", argv[0]);
		return (1);
	}
	init_game(&game);
	if (!parse_cub_file(&game, argv[1]))
	{
		printf("Parsing failed\n");
		free_game(&game);
		return (1);
	}
	free_game(&game);
	return (0);
}
