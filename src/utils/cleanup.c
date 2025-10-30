/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: almeekel <almeekel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/30 19:40:06 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/30 19:57:16 by almeekel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	cleanup_loop(t_game *game, int i)
{
	while (i < 4)
	{
		if (game->textures[i].mlx_img)
		{
			mlx_destroy_image(game->data.mlx_ptr, game->textures[i].mlx_img);
			game->textures[i].mlx_img = NULL;
		}
		i++;
	}
}

void	cleanup_all(t_game *game)
{
	if (!game)
		return ;
	if (game->data.mlx_ptr)
	{
		if (game->data.img.mlx_img)
		{
			mlx_destroy_image(game->data.mlx_ptr, game->data.img.mlx_img);
			game->data.img.mlx_img = NULL;
		}
		cleanup_loop(game, 0);
		if (game->data.win_ptr)
		{
			mlx_destroy_window(game->data.mlx_ptr, game->data.win_ptr);
			game->data.win_ptr = NULL;
		}
		mlx_destroy_display(game->data.mlx_ptr);
		free(game->data.mlx_ptr);
		game->data.mlx_ptr = NULL;
	}
	free_game(game);
}