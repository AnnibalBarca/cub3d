/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 18:33:37 by nagaudey          #+#    #+#             */
/*   Updated: 2025/10/26 14:23:10 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	put_pixel(t_game *game, int x, int y, unsigned int color)
{
	char	*pixel;

	if (x < 0 || x >= WIN_WIDTH || y < 0 || y >= WIN_HEIGHT)
		return ;
	pixel = game->data.img.addr + (y * game->data.img.line_len + x * (game->data.img.bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_square(t_game *game, int x, int y, int width, int height, int color)
{
    int	i;
    int	j;

    i = 0;
    while (i < height)
    {
        j = 0;
        while (j < width)
        {
            put_pixel(game, x + j, y + i, color);
            j++;
        }
        i++;
    }
}

void	draw_map(t_game *game)
{
    int	i;
    int	j;
    int	tile_size;
    int	color;

    tile_size = 32;
    i = 0;
    while (i < game->map_height)
    {
        j = 0;
        while (j < game->map_width)
        {
            if (game->map[i][j] == '1')
                color = 0x808080;
            else if (game->map[i][j] == '0')
                color = 0xFFFFFF;
            else if (game->map[i][j] == 'N')
                color = 0xFF0000;
            else
                color = 0x000000;
            draw_square(game, j * tile_size, i * tile_size, tile_size, tile_size, color);
            j++;
        }
        i++;
    }
}

