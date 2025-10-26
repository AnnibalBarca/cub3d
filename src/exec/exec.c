/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/19 18:41:58 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/26 18:46:39 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	close_win(t_game *game)
{
    if (game->data.img.mlx_img)
        mlx_destroy_image(game->data.mlx_ptr, game->data.img.mlx_img);
    mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
    free_game(game);
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

int	render(t_game *game)
{
    calc_timeframe(game);
    handle_rotation(game);
    handle_right_and_left(game);
    handle_up_and_down(game);
	draw_map(game);
    draw_minimap(game);
    mlx_put_image_to_window(game->data.mlx_ptr, game->data.win_ptr,
        game->data.img.mlx_img, 0, 0);
    draw_minimap_compass(game);
    return (0);
}

int	exec(t_game *game)
{
    game->data.mlx_ptr = mlx_init();
    if (!game->data.mlx_ptr)
        return (1);
    init_mmap(game);
    game->data.win_ptr = mlx_new_window(game->data.mlx_ptr, game->screen_width,
            game->screen_height, "cub3d");
    if (!game->data.win_ptr)
    {
        mlx_destroy_display(game->data.mlx_ptr);
        free(game->data.mlx_ptr);
        return (1);
    }
    game->data.img.mlx_img = mlx_new_image(game->data.mlx_ptr, game->screen_width,
            game->screen_height);
    game->data.img.addr = mlx_get_data_addr(game->data.img.mlx_img,
            &game->data.img.bpp, &game->data.img.line_len,
            &game->data.img.endian);
    mlx_loop_hook(game->data.mlx_ptr, &render, game);
    mlx_hook(game->data.win_ptr, KeyPress, KeyPressMask, &handle_keypress,
        game);
    mlx_hook(game->data.win_ptr, KeyRelease, KeyReleaseMask, &handle_keyrelease,
        game);
    mlx_hook(game->data.win_ptr, DestroyNotify, StructureNotifyMask, &close_win,
        game);
    mlx_loop(game->data.mlx_ptr);
    return (0);
}
