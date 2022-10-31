/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:42 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/31 13:03:59 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

void	set_map_check(t_coord *map_check, t_map *map)
{
	map_check->x = map->player->x;
	map_check->y = map->player->y;
}

void	init_map_check_ray_dir(t_ray *ray, t_coord *map_check,
			t_map *map, t_fcoord *step)
{
	set_map_check(map_check, map);
	if (ray->dir.x < 0)
	{
		step->x = -1;
		ray->length_1d.x = (ray->start.x - (float)map_check->x)
			* ray->step_size.x;
	}
	else
	{
		step->x = 1;
		ray->length_1d.x = ((float)map_check->x + 1 - ray->start.x)
			* ray->step_size.x;
	}
	if (ray->dir.y < 0)
	{
		step->y = -1;
		ray->length_1d.y = (ray->start.y - (float)map_check->y)
			* ray->step_size.y;
	}
	else
	{
		step->y = 1;
		ray->length_1d.y = ((float)map_check->y + 1 - ray->start.y)
			* ray->step_size.y;
	}
}

void	update_distancex(t_coord *map_check,
		t_fcoord *step, t_ray *ray, float	*distance)
{
	map_check->x += step->x;
	*distance = ray->length_1d.x;
	ray->length_1d.x += ray->step_size.x;
	ray->xmin = 1;
}

void	update_distancey(t_coord *map_check,
		t_fcoord *step, t_ray *ray, float	*distance)
{
	map_check->y += step->y;
	*distance = ray->length_1d.y;
	ray->length_1d.y += ray->step_size.y;
	ray->xmin = 0;
}

float	walk_shortest_path(t_ray *ray, t_coord *map_check,
	t_fcoord *step, t_map *map)
{
	bool		tile_found;
	float		max_distance;
	float		distance;

	tile_found = false;
	max_distance = 2000;
	distance = 0;
	while (!tile_found && distance < max_distance)
	{
		if (ray->length_1d.x < ray->length_1d.y)
			update_distancex(map_check, step, ray, &distance);
		else
			update_distancey(map_check, step, ray, &distance);
		if (map_check->x >= 0 && map_check->x < map->xlen
			&& map_check->y >= 0 && map_check->y < map->ylen)
		{
			if (map->coord[map_check->y][map_check->x] == '1'
				|| map->coord[map_check->y][map_check->x] == 'C')
				tile_found = getdoorlen(ray, distance,
						map->coord[map_check->y][map_check->x]);
		}
	}
	return (distance);
}
