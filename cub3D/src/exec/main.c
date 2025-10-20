/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:41:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/20 10:06:20 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
	mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
	// FREE ALL
	mlx_destroy_display(game->data.mlx_ptr);
	free(game->data.mlx_ptr);
	exit(0);
	return (0);
}

int	handle_keypress(int keysym, t_game *game)
{
	if (keysym == XK_Escape)
		close_win(game);
	if (keysym == XK_w || keysym == XK_z)
		game->key.go_forward = 1;
	if (keysym == XK_s)
		game->key.go_backward = 1;
	if (keysym == XK_a || keysym == XK_q)
		game->key.go_left = 1;
	if (keysym == XK_d)
		game->key.go_right = 1;
	if (keysym == XK_Left)
		game->key.turn_left = 1;
	if (keysym == XK_Right)
		game->key.turn_right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_game *game)
{
	if (keysym == XK_w || keysym == XK_z)
		game->key.go_forward = 0;
	if (keysym == XK_s)
		game->key.go_backward = 0;
	if (keysym == XK_a || keysym == XK_q)
		game->key.go_left = 0;
	if (keysym == XK_d)
		game->key.go_right = 0;
	if (keysym == XK_Left)
		game->key.turn_left = 0;
	if (keysym == XK_Right)
		game->key.turn_right = 0;
	return (0);
}

int render(t_game *game)
{
    static double pos_x = 250;
    static double pos_y = 250;
    double move_speed = 1;
    int radius = 5;
    int x, y;

    y = pos_y - radius;
    while (y <= pos_y + radius)
    {
        x = pos_x - radius;
        while (x <= pos_x + radius)
        {
            if ((x - pos_x) * (x - pos_x) + (y - pos_y) * (y - pos_y) <= radius * radius)
                mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr, x, y, 0x00000000);
            x++;
        }
        y++;
    }

    if (game->key.go_forward)
        pos_y -= move_speed / 100;
    if (game->key.go_backward)
        pos_y += move_speed / 100;
    if (game->key.go_left)
        pos_x -= move_speed / 100;
    if (game->key.go_right)
        pos_x += move_speed / 100;

    if (pos_x < radius)
        pos_x = radius;
    if (pos_x >= game->map_width - radius)
        pos_x = game->map_width - radius - 1;
    if (pos_y < radius)
        pos_y = radius;
    if (pos_y >= game->map_height - radius)
        pos_y = game->map_height - radius - 1;

    y = pos_y - radius;
    while (y <= pos_y + radius)
    {
        x = pos_x - radius;
        while (x <= pos_x + radius)
        {
            if ((x - pos_x) * (x - pos_x) + (y - pos_y) * (y - pos_y) <= radius * radius)
                mlx_pixel_put(game->data.mlx_ptr, game->data.win_ptr, x, y, 0x00FF0000);
            x++;
        }
        y++;
    }

    return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	(void)av;
	game.data.mlx_ptr = mlx_init();
	if (!game.data.mlx_ptr)
		return (1);
	// PARSING
	init_game(&game);
	game.map_height = 500;
	game.map_width = 500;
	game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, game.map_width,
			game.map_height, "");
	if (!game.data.win_ptr)
	{
		// FREE ALL
		mlx_destroy_display(game.data.mlx_ptr);
		free(game.data.mlx_ptr);
		return (1);
	}
	mlx_loop_hook(game.data.mlx_ptr, &render, &game.data);
	mlx_hook(game.data.win_ptr, KeyPress, KeyPressMask, &handle_keypress, &game.data);
	mlx_hook(game.data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
			&game);
	mlx_hook(game.data.win_ptr, DestroyNotify, StructureNotifyMask, &close_win,
		&game);
	mlx_loop(game.data.mlx_ptr);
}