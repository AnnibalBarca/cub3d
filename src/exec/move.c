/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:27:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/27 18:26:13 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	move_player(t_game *game, double delta_x, double delta_y)
{
	double	nx;
	double	ny;

	nx = game->player.pos_x + delta_x;
	ny = game->player.pos_y + delta_y;
	if (game->map[(int)game->player.pos_y][(int)nx] != '1')
		game->player.pos_x = nx;
	if (game->map[(int)ny][(int)game->player.pos_x] != '1')
		game->player.pos_y = ny;
}

void	rotate_left(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(-rot_speed)
		- game->player.dir_y * sin(-rot_speed);
	game->player.dir_y = old_dir_x * sin(-rot_speed) + game->player.dir_y
		* cos(-rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(-rot_speed)
		- game->player.plane_y * sin(-rot_speed);
	game->player.plane_y = old_plane_x * sin(-rot_speed) + game->player.plane_y
		* cos(-rot_speed);
}

void	rotate_right(t_game *game, double rot_speed)
{
	double	old_dir_x;
	double	old_plane_x;

	old_dir_x = game->player.dir_x;
	game->player.dir_x = game->player.dir_x * cos(rot_speed)
		- game->player.dir_y * sin(rot_speed);
	game->player.dir_y = old_dir_x * sin(rot_speed) + game->player.dir_y
		* cos(rot_speed);
	old_plane_x = game->player.plane_x;
	game->player.plane_x = game->player.plane_x * cos(rot_speed)
		- game->player.plane_y * sin(rot_speed);
	game->player.plane_y = old_plane_x * sin(rot_speed) + game->player.plane_y
		* cos(rot_speed);
}

void	handle_rotation(t_game *game)
{
	double	rot_speed;

	if (game->delta_time <= 0.0f)
		return ;
	rot_speed = ROTATION_SPEED * game->delta_time;
	if (game->key.turn_right)
		rotate_right(game, rot_speed);
	if (game->key.turn_left)
		rotate_left(game, rot_speed);
}

void	handle_up_and_down(t_game *game)
{
	double	speed;
	double	dx;
	double	dy;

	if (game->delta_time <= 0.0f)
		return ;
	speed = WALK_SPEED * game->delta_time;
	if (game->key.go_forward)
	{
		dx = game->player.dir_x * speed;
		dy = game->player.dir_y * speed;
		move_player(game, dx, dy);
	}
	if (game->key.go_backward)
	{
		dx = -game->player.dir_x * speed;
		dy = -game->player.dir_y * speed;
		move_player(game, dx, dy);
	}
}

void	handle_right_and_left(t_game *game)
{
	double	speed;
	double	dx;
	double	dy;

	if (game->delta_time <= 0.0f)
		return ;
	speed = WALK_SPEED * game->delta_time;
	if (game->key.go_right)
	{
		dx = -game->player.dir_y * speed;
		dy = game->player.dir_x * speed;
		move_player(game, dx, dy);
	}
	if (game->key.go_left)
	{
		dx = game->player.dir_y * speed;
		dy = -game->player.dir_x * speed;
		move_player(game, dx, dy);
	}
}
