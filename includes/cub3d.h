/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nagaudey <nagaudey@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/13 15:14:57 by almeekel          #+#    #+#             */
/*   Updated: 2025/10/27 17:42:36 by nagaudey         ###   ########.fr       */
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
#include <float.h>
# include <sys/time.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "../minilibx-linux/mlx.h"
# define WIN_HEIGHT 1500
# define WIN_WIDTH  2000
# define MAP_HEIGHT 500
# define MAP_WIDTH	500
# define WALK_SPEED	3
# define ROTATION_SPEED 4
# define PI 3.14159265359
# define MINIMAP_RADIUS 80


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

typedef struct s_img
{
	void		*mlx_img;
	char		*addr;
	int			bpp;
	int			line_len;
	int			endian;
	int			w;
	int			h;
}				t_img;

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
	char		player_letter;
}				t_player;

typedef struct	s_data
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
}				t_data;

typedef struct s_ray
{
	double		raydir_x;
	double		raydir_y;
	double		angle;
	double		camera_x;
	double		delta_distx;
	double		delta_disty;
	int			map_x;
	int			map_y;
	int			step_x;
	int			step_y;
	double		side_disty;
	double		side_distx;
	int			hit;
	double		perp_dist;
	double		line_height;
	double		wall_x;
	double		draw_start;
	double		draw_end;
	int			tex_x;
	int			tex_y;
	int			side;
	int			iter_limit;
}				t_ray;

typedef struct s_minimap
{
	int	cx;
	int	cy;
	int	radius;
	int	scale;
	int	map_width;
	int	map_height;
	int	px;
	int	py;
}	t_minimap;

typedef struct s_game
{
	t_data		data;
	t_key		key;
	char		**map;
	int			map_width;
	int			map_height;
	t_img		textures[4];
	t_ray		raycast;
	t_color		floor_color;
	t_color		ceiling_color;
	t_player	player;
	t_minimap	mmap;
	char		*path_north;
	char		*path_south;
	char		*path_east;
	char		*path_west;
	int			has_tex_no;
	int			has_tex_so;
	int			has_tex_we;
	int			has_tex_ea;
	int			has_floor_color;
	int			has_ceiling_color;
	int			screen_width;
	int			screen_height;
	double		last_time;
	double		delta_time;
}				t_game;

/* Main parsing pipeline */
int				parse_cub_file(t_game *game, char *filename);
void			free_game(t_game *game);

/* Init functions */
void	init_game(t_game *game);
void	set_vector(t_player *player);
void	set_camera(t_player *player);

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
int				print_e(char *str, int status);



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

/* Exec functions*/

void	handle_rotation(t_game *game);
void	handle_up_and_down(t_game *game);
void	handle_right_and_left(t_game *game);
double	calc_timeframe(t_game *game);
void	draw_map(t_game *game);
int		exec(t_game *game);
void	draw_minimap(t_game *game);
void	draw_minimap_compass(t_game *game);
void	put_pixel(t_game *game, int x, int y, unsigned int color);
void	init_mmap(t_game *game);

// DDA functions
int    dda_register_hit(t_ray *r);


#endif
