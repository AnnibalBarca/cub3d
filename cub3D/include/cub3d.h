#ifndef CUB3D_H
# define CUB3D_H

# include "../libft/libft.h"
# include <stddef.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <errno.h>

typedef struct s_color
{
    int r;
    int g;
    int b;
}   t_color;

typedef struct s_textures
{
    char *north;
    char *south;
    char *west;
    char *east;
}   t_textures;

typedef struct s_player
{
    int     x;
    int     y;
    char    dir;    /* 'N','S','E','W' */
    int     count;  /* should be exactly 1 after parsing */
}   t_player;

typedef struct s_game
{
    /* Map representation (array of strings, each row as in the file) */
    char        **map;
    int         map_width;     /* max visible characters per row (no trailing \n) */
    int         map_height;    /* number of non-empty map rows */

    /* Textures and colors parsed from header */
    t_textures  textures;
    t_color     floor_color;
    t_color     ceiling_color;

    /* Player discovered while parsing */
    t_player    player;

    /* Presence flags for required elements from header (NO,SO,WE,EA,F,C) */
    int         has_tex_no;
    int         has_tex_so;
    int         has_tex_we;
    int         has_tex_ea;
    int         has_floor_color;
    int         has_ceiling_color;

    /* Optional: desired screen/window size determined from map or config */
    int         screen_width;
    int         screen_height;

    /* Any parsing errors may set errno and call the helpers below */
}   t_game;

/* Parsing and validation functions (implementations are part of parsing) */
int     parse_map(t_game *game, char *map_file);
/* parsing helpers for header lines */
int     parse_texture_line(char *line, t_game *game);
int     parse_color_line(char *line, t_game *game, int is_floor);
int     parse_map_lines(char *content, t_game *game);
void    char_checker(char *content, t_game *game);
void    rectangular_checker(t_game *game);
void    walled_checker_columns(t_game *game);
int     player_collectibles_exit_checker(t_game *game);
void    check_screen_size(t_game *game);

/* Error helpers (parsing should call these on fatal problems) */
void    error_exit(const char *msg, t_game *game);
void    error_message(const char *msg);

/* Utilities */
int     tab_len(char **tab);

#endif /* CUB3D_H */
