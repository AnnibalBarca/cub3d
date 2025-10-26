/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 15:27:04 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/26 21:18:29 by nagaudey         ###   ########.fr       */
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

void	normalize_angle(double *angle)
{
    while (*angle >= 360.0)
        *angle -= 360.0;
    while (*angle < 0.0)
        *angle += 360.0;
}

void	handle_rotation(t_game *game)
{
    double	speed;

    if (game->delta_time <= 0.0f)
        return ;
    speed = ROTATION_SPEED * game->delta_time;
    if (game->key.turn_right)
        game->player.direction += speed;
    if (game->key.turn_left)
        game->player.direction -= speed;
    normalize_angle(&game->player.direction);
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
