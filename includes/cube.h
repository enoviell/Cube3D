/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dcologgi <dcologgi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/30 10:58:59 by rbordin           #+#    #+#             */
/*   Updated: 2023/11/16 17:31:31 by dcologgi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <math.h>
# include <stdint.h>
# include "texture.h"
# include "../mlx_linux/mlx.h"

# define BUFFER_SIZE 100

# define WIDTH 24
# define HEIGHT 24
# define WIN_WIDTH 1280
# define WIN_HEIGHT 960

# define MINIMAP 200
# define MINIMAP_S 10

# define PI 3.14159
# define MOVSPEED 0.6
# define ROTSPEED 0.1

# define PLAYER_R 10
# define F 0x000089AD
# define C 0x00403125

typedef struct s_cube {
	void				*mlx;
	void				*mlx_win;
	char				**map;
	int					map_w;
	int					map_h;
	int					minimap[2];
	int					a_phase;
	int					f[3];
	int					c[3];
	int					t[6];
	struct s_img		*img;
	struct s_player		*player;
	struct s_ray		*ray;
	struct s_textures	*texts;
	struct s_door		*door;
}				t_cube;

typedef struct s_player{
	double	cam_side;
	double	pos[2];
	double	dir[2];
	double	cam_plane[2];
}			t_player;

typedef struct s_ray {
	int		pos[2];
	int		draw[2];
	int		incr[2];
	int		ray_id;
	int		side;
	int		wall_height;
	int		lenght;
	int		texx;
	double	dir[2];
	double	side_dist[2];
	double	delta_dist[2];
	double	wallx;
	double	step;
	double	texpos;
	double	wall_dist;
}			t_ray;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}				t_img;

typedef struct s_tex {
	t_img	xpm;
	int		w;
	int		h;
}			t_tex;

typedef struct s_textures {
	t_tex			wall_ns;
	t_tex			wall_ew;
	t_tex			no;
	t_tex			so;
	t_tex			we;
	t_tex			ea;
	t_tex			door;
}			t_textures;

typedef struct s_door
{
	int				x;
	int				y;
	double			dist;
}				t_door;

//			srcs/utils/char_utils.c
int				valid_char(const char *stack, char c);
void			find_char(char **map, int *ids);

//			srcs/utils/ft_abs.c
double			absf(double i);

//			srcs/utils/ft_atoi.c
int				ft_atoi(const char *str);

//			srcs/utils/ft_calloc.c
void			*ft_calloc(size_t count, size_t size);

//			srcs/utils/ft_memset.c
void			*ft_memset(void *b, int c, size_t len);

//			srcs/utils/ft_split.c
char			*ft_substr(char const *s, unsigned int start, size_t len);
char			**ft_split(const char *s, char c);

//			srcs/utils/ft_strcmp.c
int				ft_strcmp(char *s1, char *s2);

//			srcs/utils/ft_strjoin.c
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_dotjoin(char const *s1, char const *s2, char *sep);
char			*ft_freejoin(char *s1, char *s2);

//			srcs/utils/ft_strreplace.c
char			*ft_strreplace(char const *src, char *stack, char *paste);

//			srcs/utils/gnl_utils.c
char			*ft_strmerge(char *buff, char *tmp_buff);
int				ft_find_line(char *s);
char			*ft_return_line(char *buff);
char			*ft_prepare_next(char *buff);

//			srcs/utils/gnl.c
char			*get_next_line(int fd);

//			srcs/utils/mapvalidator.c
int				validate_map(t_cube *game);

//			srcs/utils/map.c
int				map_init(t_cube *game, int fd);
void			put_wall_on_space(char **mat, char *stack, char *paste);
char			**expand_mat(char **mat, char *str);
void			map_error(char *error);

//			srcs/utils/mat_utils.c
void			free_mat(char **mat);
int				ft_matlen(char **arr);
void			ft_matcopy(char **src, char **dst, int start);

//			srcs/utils/parser.c
int				parser(t_cube *game, t_textures *texts, char *path);

//			srcs/utils/str_utils.c
size_t			ft_strlen(const char *s);
char			*create_string(char c, int size);

//			srcs/raycast/found_wall.c
void			found_wall(t_cube *game, t_ray *ray);

//			srcs/raycast/draw.c
void			draw_pixel_column(t_cube *game, int x, t_ray *ray, t_img *img);
void			display_cross(t_img *img);

//			srcs/raycast/load_textures.c
int				load_text_walls(t_cube *game, t_tex *tex, char **path, int pos);
int				load_text_door(t_cube *game, t_tex *tex, char *path);
void			find_door(t_cube *game);

//			srcs/raycast/pixel_put.c			
void			my_mlx_pixel_put(t_img *data, int x, int y, unsigned int color);

//			srcs/raycast/raycast.c
int				raycast(t_cube *game, t_img *img, t_ray *ray);

//			srcs/raycast/rgbutility.c
int				get_rgb(char *addr, int x, int y);
int				load_background(t_cube *game, char **s, char c, int culo);
unsigned long	create_rgb(int r, int g, int b);
unsigned long	get_pixel(t_img *img, int x, int y);

//			srcs/main/cub3d.c
int				end_game(t_cube *game);

//			srcs/main/init.c
void			init_directions(t_cube *game, t_player *player);
void			init_cube(t_cube *game, t_img *img, t_textures *texts,
					char *path);
void			init_texture(t_cube *game, t_textures *texts);

//			srcs/main/keys.c
int				key_filter(int keycode, t_cube *game);
//int				mouse_filter(int x, int y, t_cube *game);

//			srcs/main/minimap_utils.c
void			wall_square(t_img *img, int len, int offset_x, int offset_y);
void			floor_square(t_img *img, int len, int offset_x, int offset_y);
void			outside_square(t_img *img, int len, int offset_x, int offset_y);
void			door_square(t_img *img, int len, int offset_x, int offset_y);
void			player_square(t_img *img, int len, int offset_x, int offset_y);

//			srcs/main/minimap.c
void			render_minimap(t_cube *game);

//			srcs/main/moves.c
void			camera_rotation(t_cube *game, double dir, double speed);
void			move_up_down(t_cube *game, double dir);
void			move_left_right(t_cube *game, double dir);
void			open_door(t_cube *game);

//			srcs/main/set.c
void			set_player(t_player *player, char c);

#endif
