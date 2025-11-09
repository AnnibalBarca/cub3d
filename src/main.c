/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 14:02:20 by almeekel          #+#    #+#             */
/*   Updated: 2025/11/09 18:59:42 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	free_game(t_game *game)
{
	int	i;

	if (game->path_north)
		free(game->path_north);
	if (game->path_south)
		free(game->path_south);
	if (game->path_west)
		free(game->path_west);
	if (game->path_east)
		free(game->path_east);
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

static int	parse_input(t_game *game, int fd)
{
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
	if (!parse_map(game, fd))
	{
		close(fd);
		return (0);
	}
	return (1);
}

int	parse_cub_file(t_game *game, char *filename)
{
	int	fd;

	if (ft_strlen(filename) < 5 || ft_strncmp(&filename[ft_strlen(filename)
				- 4], ".cub", 4) != 0)
		return (print_e("Invalid file extension (expected .cub)\n", 0));
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (print_e("Failed to open file\n", 0));
	if (!parse_input(game, fd))
		return (0);
	close (fd);
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
	exec(&game);
	free_game(&game);
	return (0);
}
