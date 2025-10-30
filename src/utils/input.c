/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:39:17 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/30 19:40:33 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
