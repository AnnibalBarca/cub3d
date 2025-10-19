/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:41:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/19 20:54:51 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <cub3d.h>

int	handle_keypress(int keysym, t_key *key)
{
	if (keysym == XK_Escape)
		//close()
	if (keysym == XK_w || keysym == XK_z)
		key->go_forward = 1;
	if (keysym == XK_s)
		key->go_backward = 1;
	if (keysym == XK_a || keysym == XK_q)
		key->go_left = 1;
	if (keysym == XK_d)
		key->go_right = 1;
	if (keysym == XK_Left)
		key->turn_left = 1;
	if (keysym == XK_Right)
		key->turn_right = 1;
	return (0);
}

int	handle_keyrelease(int keysym, t_key *key)
{
	if (keysym == XK_w || keysym == XK_z)
		key->go_forward = 0;
	if (keysym == XK_s)
		key->go_backward = 0;
	if (keysym == XK_a || keysym == XK_q)
		key->go_left = 0;
	if (keysym == XK_d)
		key->go_right = 0;
	if (keysym == XK_Left)
		key->turn_left = 0;
	if (keysym == XK_Right)
		key->turn_right = 0;
	return (0);
}

int	main(int ac, char **av)
{
	t_game	game;

	(void)ac;
	game.data.mlx_ptr = mlx_init();
	if (!game.data.mlx_ptr)
		return (1);
	// PARSING
	game.data.win_ptr = mlx_new_window(game.data.mlx_ptr, game.map_width * ??,
			game.map_height * ??, "");
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
			&game.key);
	mlx_hook(game.data.win_ptr, DestroyNotify, StructureNotifyMask, &close,
		&game.key);
	mlx_loop(game.data.mlx_ptr);
}