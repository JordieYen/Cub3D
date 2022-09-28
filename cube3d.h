/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/09/27 20:07:20 by bunyodshams      ###   ########.fr       */
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
# define PI 3.14159265

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
	int		xlen;
	int		ylen;
	void		*mlx;
	void		*win;
	t_data		*img;
	t_player	*player;
	t_ray		*rays;
}	t_map;

// ft_cube_utils.c
void	put_p(t_data *data, int x, int y, int color);
void    draw_two_points(t_map *map, int x1, int y1, int x2, int y2);

#endif