/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:42 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/23 02:03:08 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"

void	init_map_check_ray_dir(t_ray *ray, t_coord *map_check, t_map *map, t_fcoord *step)
{
    map_check->x = map->player->x;
	map_check->y = map->player->y;
    if (ray->dir.x < 0)
	{
		step->x = -1;
		ray->length_1d.x = (ray->start.x - (float)map_check->x) * ray->step_size.x;
	}
	else
	{
		step->x = 1;
		ray->length_1d.x = ((float)map_check->x + 1 - ray->start.x) * ray->step_size.x;
	}
	if (ray->dir.y < 0)
	{
		step->y = -1;
		ray->length_1d.y = (ray->start.y - (float)map_check->y) * ray->step_size.y;
	}
	else
	{
		step->y = 1;
		ray->length_1d.y = ((float)map_check->y + 1 - ray->start.y) * ray->step_size.y;
	}
}

float	rotate_angle(float angle)
{
	angle += DR/21.3333;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

float	walk_shortest_path(t_ray *ray, t_coord *map_check, t_fcoord *step, t_map *map)
{
	bool		tile_found;
	float		maxDistance;
	float		distance;

	tile_found = false;
	maxDistance = 2000;
	distance = 0;
	while (!tile_found && distance < maxDistance)
	{
		if (ray->length_1d.x < ray->length_1d.y)
		{
			map_check->x += step->x;
			distance = ray->length_1d.x;
			ray->length_1d.x += ray->step_size.x;
			ray->xmin = 1;
		}
		else
		{
			map_check->y += step->y;
			distance = ray->length_1d.y;
			ray->length_1d.y += ray->step_size.y;
			ray->xmin = 0;
		}
		if (map_check->x >= 0 && map_check->x < map->xlen && map_check->y >= 0 && map_check->y < map->ylen)
		{
			if (map->coord[map_check->y][map_check->x] == '1')
				tile_found = true;
		}
	}
	return (distance);
}