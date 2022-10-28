/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:42 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/28 19:54:17 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

void	init_map_check_ray_dir(t_ray *ray, t_coord *map_check,
			t_map *map, t_fcoord *step)
{
	map_check->x = map->player->x;
	map_check->y = map->player->y;
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

float	rotate_angle(float angle)
{
	angle += DR / 16;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}

int	getdoorlen(t_ray *ray, float distance, char c)
{
	float	ca;
	float	dist_t;

	if (c == '1')
		return (true);
	if (ray->firstdoor == 1)
		return (false);
	ca = ray->playerangle - ray->angle;
	dist_t = distance * BLK_WDT_PXL;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	if (dist_t != -1)
		dist_t = dist_t * cos(ca);
	ray->doorlen = dist_t;
	ray->doorxmin = ray->xmin;
	ray->isdoor = 'y';
	ray->doorx = (ray->start.x + ray->dir.x * distance);
	ray->doory = (ray->start.y + ray->dir.y * distance);
	ray->firstdoor = 1;
	return (false);
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
