/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:32:54 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/31 17:07:27 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

void	init_mycoord(t_coord *coord, int x1, int y1)
{
	coord->x = x1;
	coord->y = y1;
}

void	put_p(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 810 && x < 1440 && y > 0 && x > 0)
	{
		dst = data->addr + (y * data->line_length + x
				* (data->bits_per_pixel / 8));
		*(unsigned int *)dst = color;
	}
}

float	dist(int x1, int y1, int x2, int y2)
{
	float	hypo;

	hypo = sqrt(pow(x1 - x2, 2) + pow(y1 - y2, 2));
	return (hypo);
}

static int	i_s(int num1, int num2)
{
	if (num1 < num2)
		return (1);
	return (-1);
}

void	connectdots(t_data *img, t_coord coord0, t_coord coord1, int color)
{
	t_coord	d;
	t_coord	s;
	t_coord	e;

	init_mycoord(&d, abs(coord1.x - coord0.x), -abs(coord1.y - coord0.y));
	init_mycoord(&s, i_s(coord0.x, coord1.x), i_s(coord0.y, coord1.y));
	init_mycoord(&e, d.x + d.y, 0);
	while (1)
	{
		put_p(img, coord0.x, coord0.y, color);
		if (coord0.x == coord1.x && coord0.y == coord1.y)
			break ;
		e.y = 2 * e.x;
		if (e.y >= d.y)
		{
			e.x += d.y;
			coord0.x += s.x;
		}
		if (e.y <= d.x)
		{
			e.x += d.x;
			coord0.y += s.y;
		}
	}
}

// void	draw_2d_rays(t_map *map, int raynum)
// {
// 	int		i;
// 	t_coord	coord1;
// 	t_coord	coord2;

// 	i = -1;
// 	init_mycoord(&coord1, map->player->x * BLK_WDT_PXL,
// 		map->player->y * BLK_WDT_PXL);
// 	while (++i < raynum)
// 	{
// 		init_mycoord(&coord2, map->rays[i]->x * BLK_WDT_PXL,
// 			map->rays[i]->y * BLK_WDT_PXL);
// 		connectdots(map->img, coord1, coord2, 0x330066);
// 	}
// }
