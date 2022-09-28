/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cube_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/27 18:32:54 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/09/27 20:07:16 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <math.h>

void	put_p(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 1080 && x < 1920)
	{
		if (y > 0 && x > 0)
		{
			dst = data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void    draw_two_points(t_map *map, int x1, int y1, int x2, int y2)
{
    int hypo;
    int i;
	float anglex;
	float angley;
	float aTan;

    i = -1;
    hypo = sqrt(((x1 - x2) * (x1 - x2)) + ((y1 - y2) * (y1 - y2)));
	aTan = -1/tan(map->rays[i].angle);
	anglex = aTan * (x1 - x2);
	angley = aTan * (y1 - y2);
    while (++i < hypo)
	{
		put_p(map->img, ((map->player->x * BLK_WDT) + map->player->x) + (anglex * i), (i * BLK_WDT) + map->player->y + (angley * i), 0xFFFF00);	
	}
}