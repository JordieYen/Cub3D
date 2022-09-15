/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:10:30 by jking-ye          #+#    #+#             */
/*   Updated: 2022/09/15 14:37:32 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include "mlx.h"
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include <stdio.h>
# include <math.h>

typedef struct s_map
{
	char	**coord;
	int		xlen;
	int		ylen;
}	t_map;

// typedef struct s_cartesian
// {
// 	t_coord		**coords;
// 	int			xlen;
// 	int			ylen;
// }	t_cartesian;

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
	// t_cartesian	*chart;
}	t_vars;

#endif