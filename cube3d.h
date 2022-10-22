/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/22 21:07:22 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define W 13
# define A 0
# define S 1
# define D 2
# define WIN_H 810
# define WIN_W 1440
# define BLK_WDT 1
# define BLK_WDT_PXL 32
# define STP_SZ 0.1
# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533
#include <stdbool.h>

typedef struct s_player
{
	float x;
	float y;
	float angle;
	float dx;
	float dy;
} t_player;

typedef struct s_rgb
{
	int red;
	int green;
	int blue;
} t_rgb;

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
} t_xmp_data;

typedef struct s_ray
{
	int		*ray_rgbs;
	float	angle;
	float	x;
	float	y;
	float	xof;
	float	yof;
	float	len;
	int		up;
	int		left;
	int		magnitude;
	t_rgb	rgb;
	char	side;
	int		xmin;
	t_fcoord max;
	t_fcoord start;
	t_fcoord dir;
	t_fcoord step_size;
	t_fcoord length_1d;
} t_ray;

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
	void	*wall;
	int		wall_width;
	int		wall_height;
	t_xmp_data xpm_data;
}	t_wall;

typedef struct s_map
{
	char	**coord;
	char	direction;
	int		xlen;
	int		ylen;
	long int	last_frame;
	int			fps;
	void		*mlx;
	void		*win;
	t_wall		wall_n;
	t_data		*img;
	t_player	*player;
	t_ray		**rays;
}	t_map;

// ft_cube_utils.c
void	put_p(t_data *data, int x, int y, int color);
void    draw_two_points(t_map *map, int x1, int y1, int x2, int y2);
float	dist(int x1, int y1, int x2, int y2);
void	draw_2d_rays(t_map *map, int raynum);
void	init_mycoord(t_coord *coord, int x1, int y1);
void	connectdots(t_data *img, t_coord coord0, t_coord coord1, int color);

// hex_tools.c
char	*ft_itoh(int decimal);
int		ft_htoi(char *hex);

// ft_shadows.c
int	darken_rgb(int rgb, float len);

// ft_textures.c
void	create_line_colors(t_map *map, int ray_num);
t_rgb	**create_xmp_array(t_map *map, t_xmp_data *xmpdata);
void	get_textures(t_map *map);
void	connect_dots_colors(t_map *map, int x, int height, t_ray *ray);

// render.c
void    render_background(t_map *map, int ray_num);
void	render_rays(t_map *map, int ray_num);
void	calculate_intersection(t_ray *ray, float fDistance);
t_ray	*init_ray(float angle, t_map *map);

#endif