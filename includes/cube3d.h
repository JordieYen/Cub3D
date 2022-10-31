/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/31 17:54:34 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define PI 3.14159265359
# include <stdbool.h>

typedef struct s_player
{
	char	start_char;
	float	x;
	float	y;
	float	angle;
	float	dx;
	float	dy;
}	t_player;

typedef struct s_textures
{
	char	*wall_no_dir;
	char	*wall_so_dir;
	char	*wall_we_dir;
	char	*wall_ea_dir;
	char	*wall_do_dir;
}	t_tex;

typedef struct s_rgb
{
	int	red;
	int	green;
	int	blue;
}	t_rgb;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

typedef struct s_fcoord
{
	float	x;
	float	y;
}	t_fcoord;

typedef struct s_xmp_data
{
	int		*data;
	int		bits_per_pixel;
	int		size_line;
	int		endian;
}	t_xmp_data;

typedef struct s_ray
{
	char		isdoor;
	float		doorlen;
	int			doorxmin;
	float		doorx;
	float		doory;
	int			firstdoor;
	float		angle;
	float		playerangle;
	float		x;
	float		y;
	float		xof;
	float		yof;
	float		len;
	float		door_percentange;
	int			up;
	int			left;
	int			magnitude;
	t_rgb		rgb;
	char		side;
	int			xmin;
	t_fcoord	max;
	t_fcoord	start;
	t_fcoord	dir;
	t_fcoord	step_size;
	t_fcoord	length_1d;
}	t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_wall
{
	void		*wall;
	int			wall_width;
	int			wall_height;
	t_xmp_data	xpm_data;
}	t_wall;

typedef struct s_map
{
	int				equipweapon;
	int				swapweapon;
	int				offset;
	char			**coord;
	char			direction;
	int				xlen;
	int				ylen;
	long int		last_frame;
	int				fps;
	void			*mlx;
	void			*win;
	int				map_start_n;
	t_wall			*hand;
	t_wall			knife;
	t_wall			wall_n;
	t_wall			wall_s;
	t_wall			wall_e;
	t_wall			wall_w;
	t_wall			door;
	t_data			*img;
	t_player		*player;
	t_ray			**rays;
	t_tex			*tex;
	t_coord			mouse;
	unsigned int	f_color;
	unsigned int	c_color;
}	t_map;

// cube3d.c
void		create_screen(t_map *map);
void		set_player_posix(t_map *map);

// ft_cube_utils.c
void		put_p(t_data *data, int x, int y, int color);
float		dist(int x1, int y1, int x2, int y2);
void		draw_2d_rays(t_map *map, int raynum);
void		init_mycoord(t_coord *coord, int x1, int y1);
void		connectdots(t_data *img, t_coord coord0, t_coord coord1, int color);

// ft_shadows.c
int			darken_rgb(int rgb, float len);

// ft_textures.c
void		get_textures(t_map *map);
int			pick_color(t_ray *ray, t_map *map, float percentage);
int			pick_color_door(t_ray *ray, t_map *map, float percentage);
void		connect_dots_colors(t_map *map, int x, int height, t_ray *ray);
void		connect_dots_doors(t_map *map, int x, int height, t_ray *ray);

// ft_textures_utils.c
void		get_xpm_data(t_map *map, t_wall *wall, char *texture);
void		connect_dots_colors(t_map *map, int x, int height, t_ray *ray);
void		connect_dots_doors(t_map *map, int x, int height, t_ray *ray);
int			init_texture_color(t_map *map, char *line);

// render.c
void		render_background(t_map *map, int ray_num);
void		render_rays(t_map *map, int ray_num);
void		calculate_intersection(t_ray *ray, float fDistance);
t_ray		*init_ray(float angle, t_map *map);
void		render_doors(t_map *map, int ray_num);

// ft_render_utils.c
void		init_map_check_ray_dir(t_ray *ray, t_coord *map_check,
				t_map *map, t_fcoord *step);
float		walk_shortest_path(t_ray *ray, t_coord *map_check,
				t_fcoord *step, t_map *map);

// ft_render_utils_2.c
float		rotate_angle(float angle);
int			getdoorlen(t_ray *ray, float distance, char c);

// cube_doors.c
void		handledoors(t_map *map);
void		closedoor(t_map *map);
void		opendoor(t_map *map);
int			check_if_valid(t_map *map, int offset, char door, char axis);

// cube_parser.c
void		init_map(t_map *map, int fd);
void		fill_map(t_map *map, int fd);
int			check_walls(t_map *map);
int			check_cub(t_map *map, char *config_map);

// cube_parser_utils.c
void		init_zero(t_map *map);
void		init_texture(t_map *map, char *line);
void		init_color(t_map *map, char *line);
int			textures_color_filled(t_map *map, int flag);
int			free_pp(char **str);

// cube_mouse.c
int			read_mouse(int x, int y, t_map *map);
int			deal_key(int key, t_map *map);
void		move_player(t_map *map, int key);

// frees.c
void		free_coord(t_map *map);
void		free_texture(t_map *map);
void		free_hand(t_map *map);
void		free_walls(t_map *map);
void		free_map(t_map *map);

// weapon_manipulation.c
void		equipweapon(t_map *map);
void		swapweapon(t_map *map);

// render_minimap.c
void		draw_player(t_map *map, int x, int y);
void		render_minimap(t_map *map, int start_x, int start_y, int size);
void		draw_minimap(t_map *map);

// frames.c
t_wall		changeframe(t_map *map);
void		animatehand(t_map *map);
int			render_screen(void *varg);

// cube_extra.c
void		compare_walls(char *dir, t_map *map, char **args);
void		assign_floor_ceiling_color(int rgb, t_map *map, char *line, int tc);
void		configure_map(t_map *map, int fd, char *line);
int			check_space(t_map *map, int x, int y);
void		set_start_direction(t_map *map);

#endif