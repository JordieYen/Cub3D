/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:13:51 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 17:11:00 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# include <math.h>

typedef struct s_coord
{
	int	x;
	int	y;
	int	z;
}	t_coord;

typedef struct s_cartesian
{
	t_coord		**coords;
	int			xlen;
	int			ylen;
}	t_cartesian;

typedef struct s_data
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_data;

typedef struct s_vars {
	void		*mlx;
	void		*win;
	t_data		*img;
	t_cartesian	*chart;
}	t_vars;

void		freearg(char **arg);
void		drawgradient(t_cartesian *chart, t_data *img);
void		movetocenter(t_cartesian *chart, t_coord center);
void		copyz(t_cartesian *src, t_cartesian *dest);
void		updatez(t_cartesian *chart);
void		rotatechart(t_data *img, t_cartesian *chart, t_coord center);
void		rotatedot(t_coord coord, t_coord center, t_coord *newchart);
void		get_z(t_cartesian *chart, char *file, int xlen, int ylen);
void		get_row_z(t_cartesian *chart, char *line, int xlen);
void		get_x(t_cartesian *chart, int start, int space);
void		get_y(t_cartesian *chart, int start, int space);
void		init_coord(t_coord *coord, int x1, int y1, int z1);
void		init_cartesian(t_cartesian *chart, int xlength, int ylength);
void		put_p(t_data *data, int x, int y, int color);
void		freechart(t_cartesian *chart);
void		connectdots(t_data *img, t_coord coord0, t_coord coord1, int color);
int			countxlen(char *line);
int			*get_int_arr(char *line, int xlen);
t_cartesian	get_cartesian(char *file, int xlen, int ylen);
void		plot_chart(t_cartesian *chart, t_data *img);
void		drawgrid(t_cartesian *chart, t_data *img, int color);
void		fdf(t_cartesian *chart);
int			main(int argc, char **argv);

#endif