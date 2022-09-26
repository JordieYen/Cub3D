/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/09/26 17:10:05 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H
# define W 13
# define A 0
# define S 1
# define D 2

typedef struct s_player
{
	int x;
	int y;
	int	xmap;
	int	ymap;
} t_player;

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
}	t_map;

// typedef struct s_cartesian
// {
// 	t_coord		**coords;
// 	int			xlen;
// 	int			ylen;
// }	t_cartesian;

#endif