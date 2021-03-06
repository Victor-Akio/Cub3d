/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:04:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 04:24:23 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>
# include <fcntl.h>
# include "libft.h"
# include "mlx.h"
# include "sys/stat.h"

# define PI 3.14159265
# define RADIAN 0.0174533
# define NV 270
# define EV 180
# define SV 90
# define WV 0

# define KEY_ESC 65307
# define KEY_A 97
# define KEY_D 100
# define KEY_W 119
# define KEY_S 115
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define X11_KEYPRESS 2
# define X11_DESTROY 17

# define TILE_SIZE 20
# define GAME_TITLE "Cub3d"

typedef struct		s_dxy
{
	double			x;
	double			y;
}					t_dxy;

typedef struct		s_xy
{
	int				x;
	int				y;
}					t_xy;

typedef struct		s_player
{
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			map;
	char			way;
	char			**face[4];
	double			dist;
}					t_player;

typedef struct		s_sprites
{
	int				type;
	t_xy			pos;
	double			pdist;
	t_dxy			rel_pos;
	double			ang;
	t_dxy			side_dist;
	t_dxy			step;
	t_dxy			dir;
	int				wall;
	int				side;
	t_xy			draw;
}					t_sprites;

typedef struct		s_ray
{
	t_dxy			pos;
	t_dxy			dir;
	t_dxy			delta_dist;
	t_dxy			ab_dist;
	t_dxy			step;
	double			ang;
	double			size;
	double			dist;
	double			pdist;
	double			*buffer;
	int				side;
	int				wall;
	int				spr;
}					t_ray;

typedef struct		s_tex
{
	char			*img;
	void			*mlx;
	int				w;
	int				h;
	int				bpp;
	int				line;
	int				endian;
	int				set;
}					t_tex;

typedef struct		s_map
{
	char			**map;
	int				w;
	int				h;
	int				color_w;
	int				color_f2d;
}					t_map;

typedef struct		s_img
{
	void			*img;
	char			*addr;
	int				h;
	int				w;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				fov;
}					t_img;

typedef struct		s_file
{
	char			*filename;
	char			**data;
	char			*keys[5];
}					t_file;

typedef struct		s_all
{
	void			*mlx;
	void			*win;
	t_map			map;
	t_file			file;
	t_img			img;
	t_img			minimap;
	t_ray			ray;
	t_player		player;
	t_tex			*tex;
	t_sprites		*sprites;
	double			rotation;
	double			walk;
	int				rgb_f[3];
	int				rgb_c[3];
	int				color_f;
	int				color_c;
}					t_all;

/*
** Error and exit functions
*/

int					error_exit(char *err);
int					hook_close(t_all *all);
int					exit_game(t_all *all, int ret);
int					close_button(t_all *all);

/*
**Init
*/

void				file_init(t_file *file);
void				ft_init(t_all *all);
int					ft_init2(t_all *all);
void				window_init(t_all *all, t_img *win);
int					tex_init(t_all *all);

/*
** GNL - Load File
*/

int					load_file(t_all *all, char *filename);
int					load_tex(t_all *all, char *img_addr, int i);
char				**read_file(char *filename);
void				validatescreen(t_all *all);
void				map_gen(t_all *all);
void				ft_cub_valid_map(char **matrix);
int					garead_map(t_all *all, char **mat);

/*
**Player and Movement
*/

void				rotate_horizontal(double ang, t_dxy in, t_dxy *out);
void				render_player(t_all *all);
int					player_pos(t_all *all);
void				set_hooks(t_all *all);
void				mv_up(t_all *all);
void				mv_down(t_all *all);
void				mv_right(t_all *all);
void				mv_left(t_all *all);

/*
** Textures, raycast and sprites
*/

void				draw_tex(t_all *all, int x);
void				mem_spr(t_all *all);
void				put_sprite(t_all *all, int x, int y);
void				draw_spr(t_all *all);
void				clear_sprites(t_all *all);
int					get_tex_color(t_tex *tex, int x, int y);
void				calc_rays(t_all *all);

/*
** Utils
*/

int					find_width(char **str, int beg, int end);
int					ft_max_col(char	**str);
void				my_pixel_put(t_img *img, int x, int y, int color);
int					create_trgb(int t, int r, int g, int b);
int					convert_bmp(t_all *all);
char				*next_word(char *str);
int					ft_ischarmap(char c);
int					set_color(char *line, int *dst);
void				has_walls(int x, int y, int len, char **matrix);
int					cub_str_isspace(char *line);
int					cub_str_ismap(char **cub, int id);
int					cub_handler(t_all *all, char **mat, int i);
int					valid_map(char **cub, t_all *all);
int					set_path(char **line, char *nxword);
int					set_resolution(char *line, t_all *all);

/*
** Memory
*/

char				**ft_realloc(char **str);
void				free_win(t_all *all);
void				free_tex(t_all *all);
void				free_ray(t_all *all);
void				free_map(t_all *all);

#endif
