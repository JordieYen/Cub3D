/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/09/28 19:37:47 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define W 13
# define A 0
# define S 1
# define D 2
# define BLK_WDT 64
# define STP_SZ 4
# define PI 3.14159265359
# define P2 PI/2
# define P3 3*PI/2
# define DR 0.0174533

typedef struct s_player
{
	int x;
	int y;
	int	xmap;
	int	ymap;
	float angle;
	float dx;
	float dy;
} t_player;

typedef struct s_ray
{
	float angle;
	float x;
	float y;
	float xof;
	float yof;
} t_ray;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_map
{
	char	**coord;
	char	direction;
	int		xlen;
	int		ylen;
	void		*mlx;
	void		*win;
	t_data		*img;
	t_player	*player;
	t_ray		*rays;
}	t_map;

typedef struct s_coord
{
	int	x;
	int	y;
}	t_coord;

// ft_cube_utils.c
void	put_p(t_data *data, int x, int y, int color);
void    draw_two_points(t_map *map, int x1, int y1, int x2, int y2);
float	dist(int x1, int y1, int x2, int y2);

#endif