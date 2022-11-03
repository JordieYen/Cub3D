/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_minimap.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:09:52 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/03 14:39:30 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include <stdio.h>
#include <math.h>
#include "../includes/mlx.h"
#include <float.h>
#include <stdlib.h>
#include <sys/time.h>

void	draw_player(t_map *map, int x, int y)
{
	int	color;

	color = 0x909090;
	put_p(map->img, x, y, color);
	put_p(map->img, x + 1, y, color);
	put_p(map->img, x -1, y, color);
	put_p(map->img, x, y - 1, color);
	put_p(map->img, x, y + 1, color);
	put_p(map->img, x + 1, y - 1, color);
	put_p(map->img, x - 1, y + 1, color);
	put_p(map->img, x + 1, y + 1, color);
	put_p(map->img, x - 1, y - 1, color);
	color = -1;
	while (++color < 10)
		put_p(map->img, x + (map->player->dx * color * 10),
			y + (map->player->dy * color * 10), 0x909090);
}

void	set_color(t_map *map, t_fcoord temp, int *color)
{
	if (map->coord[(int)temp.y][(int)temp.x] == '1' ||
		map->coord[(int)temp.y][(int)temp.x] == 'C')
		*color = 0x909090;
	else
		*color = 0x0E0101;
}

void	render_minimap(t_map *map, int start_x, int start_y, int size)
{
	t_coord		pos;
	t_fcoord	temp;
	int			color;

	pos.y = start_y - 1;
	temp.y = map->player->y - 3;
	while (pos.y++ < start_y + size - start_x)
	{
		temp.x = map->player->x - 3;
		pos.x = start_x - 1;
		while (pos.x++ < start_x + size - start_x)
		{
			if ((temp.x > 0 && temp.x < map->xlen)
				&& (temp.y > 0 && temp.y < map->ylen))
			{
				set_color(map, temp, &color);
				if (dist(start_x + (size / 2) - 15, start_y
						+ (size / 2) - 15, pos.x, pos.y) < 90)
					put_p(map->img, pos.x, pos.y, color);
			}
			temp.x += 0.03125;
		}
		temp.y += 0.03125;
	}
}

void	draw_minimap(t_map *map)
{
	int	size;

	size = 224;
	render_minimap(map, 30, 810 - size, size);
	draw_player(map, 30 + (size / 2) - 15, 810 - size + (size / 2) - 15);
}
