#include "cub3d.h"
#include <stdio.h>
#include <string.h>

static void	init_game(t_game *game)
{
	memset(game, 0, sizeof(t_game));
	game->map = NULL;
	game->map_width = 0;
	game->map_height = 0;
}

static void	print_game_info(t_game *game)
{
	int i;

	printf("\n=== Parsing Results ===\n");
	printf("Map width: %d\n", game->map_width);
	printf("Map height: %d\n", game->map_height);
	printf("\nMap content:\n");
	if (game->map)
	{
		i = 0;
		while (i < game->map_height && game->map[i])
		{
			printf("  [%d] %s\n", i, game->map[i]);
			i++;
		}
	}
	printf("\n");
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
	
	printf("Parsing file: %s\n", argv[1]);
	if (parse_map(&game, argv[1]))
	{
		printf("✅ Map parsed successfully!\n");
		print_game_info(&game);
		return (0);
	}
	else
	{
		printf("❌ Map parsing failed\n");
		return (1);
	}
}
