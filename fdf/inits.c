/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:13:33 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 16:51:32 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	init_coord(t_coord *coord, int x1, int y1, int z1)
{
	coord->x = x1;
	coord->y = y1;
	coord->z = z1;
}

void	init_cartesian(t_cartesian *chart, int xlength, int ylength)
{
	int	i;

	i = 0;
	chart->coords = malloc(sizeof(t_coord) * (ylength + 1));
	while (i < ylength)
	{
		chart->coords[i] = malloc(sizeof(t_coord) * (xlength + 1));
		init_coord(chart->coords[i], 0, 0, 0);
		i++;
	}
	chart->coords[i] = 0;
	chart->xlen = xlength;
	chart->ylen = ylength;
}

void	copyz(t_cartesian *src, t_cartesian *dest)
{
	int	countx;
	int	county;

	county = 0;
	while (county < (src->ylen))
	{
		countx = 0;
		while (countx < (src->xlen))
		{
			dest->coords[county][countx].z = src->coords[county][countx].z;
			countx++;
		}
		county++;
	}
}
