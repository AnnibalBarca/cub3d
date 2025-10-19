/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:14:57 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/19 20:57:01 by nagaudey         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/all.h"
# include <errno.h>
# include <fcntl.h>
# include <math.h>
# include <stddef.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
// # include <X11/X.h>
// # include <X11/keysym.h>
// # include <mlx.h>


typedef struct s_color
{
	int			r;
	int			g;
	int			b;
}				t_color;

typedef enum s_texture
{
	NORTH,
	SOUTH,
	WEST,
	EAST
}				e_texture;

typedef struct s_key
{
	int	go_forward;
	int	go_backward;
	int	go_left;
	int	go_right;
	int	turn_left;
	int	turn_right;
}	t_key;

typedef struct	s_player
{
	double		pos_x;
	double		pos_y;
	double		dir_x;
	double		dir_y;
	double		plane_x;
	double		plane_y;
}				t_player;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	int			width;
	int			height;
}				t_data;

typedef struct s_game
{
	t_data		data;
	t_key		key;
	char		**map;
	int			map_width;
	int			map_height;
	char		*tex_north;
	char		*tex_south;
	char		*tex_west;
	char		*tex_east;
	t_color		floor_color;
	t_color		ceiling_color;
	t_player	player;
	int			has_tex_no;
	int			has_tex_so;
	int			has_tex_we;
	int			has_tex_ea;
	int			has_floor_color;
	int			has_ceiling_color;
	int			screen_width;
	int			screen_height;
}				t_game;

/* Main parsing pipeline */
int				parse_cub_file(t_game *game, char *filename);
void			init_game(t_game *game);
void			free_game(t_game *game);

/* Phase 1: Parse textures (NO, SO, WE, EA) */
int				parse_textures(t_game *game, int fd);

/* Phase 2: Parse colors (F, C) */
int				parse_colors(t_game *game, int fd);

/* Phase 3: Parse map from fd (uses map_parsing.c) */
int				parse_map(t_game *game, int fd);

/* Helper: Check if all required elements are present */
int				validate_required_elements(t_game *game);

/* Map validation (from map_parsing.c) */
int				validate_map(t_game *game);
int				char_checker(t_game *game, char c);
int				walled_checker(t_game *game);

/* Error helpers (parsing should call these on fatal problems) */
void			error_exit(const char *msg, t_game *game);
void			error_message(const char *msg);

/* Map Parsing Utilities */
int				tab_len(char **tab);
int				is_player(char c);
int				is_map_char(char c);
int				is_filled_char(char c);
char			get_char_at(t_game *game, int row, int col);
int				surrounding_is_filled(int row, int col, t_game *game);

/* Parsing utilities */
char			*skip_spaces(char *str);
void			trim_end(char *str);

#endif
