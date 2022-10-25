/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:54 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/25 14:37:21 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdio.h>
#include "libmlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int		pick_color(t_ray *ray, t_map *map, float percentage)
{
	int pixel_x;
	int pixel_y;
	t_wall wall;

	if (ray->side == 'n')
		wall = map->wall_n;
	if (ray->side == 's')
		wall = map->wall_n;
	if (ray->side == 'e')
		wall = map->wall_n;
	if (ray->side == 'w')
		wall = map->wall_n;


	if (ray->side == 'n' || ray->side == 's')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray->x) - ray->x);
	}
	if (ray->side == 'e' || ray->side == 'w')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray->y) - ray->y);
	}
	
	if ((unsigned int)wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y] == 4278190080)
        return (-1);
	return (darken_rgb(wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y], ray->len));
}

int		pick_color_door(t_ray *ray, t_map *map, float percentage)
{
	int pixel_x;
	int pixel_y;
	t_wall wall;

	wall = map->door;
	if (ray->doorxmin == 0)
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray->doorx) - ray->doorx);
	}
	if (ray->doorxmin == 1)
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray->doory) - ray->doory);
	}
	
	if ((unsigned int)wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y] == 4278190080)
        return (-1);
	return (darken_rgb(wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y], ray->len));
}

void	connect_dots_doors(t_map *map, int x, int height, t_ray *ray)
{
	int	y;
	float y_offset;

	y = -1;
	y_offset = 400 - (height / 2.5) - 0.01;
	while(y++ < height - 1)
	{
		if (y_offset + y > 0 && y_offset + y < WIN_H)
		{
			if (pick_color_door(ray, map, (float)y / height) != -1)
				put_p(map->img, x, y_offset + y, pick_color_door(ray, map, (float)y / height));
		}	
	}
}

void	connect_dots_colors(t_map *map, int x, int height, t_ray *ray)
{
	int	y;
	float y_offset;

	y = -1;
	ray->angle = 0;
	y_offset = 400 - (height / 2.5) - 0.01;
	while(y++ < height)
	{
		if (y_offset + y > 0 && y_offset + y < WIN_H)
		{
			if (pick_color(ray, map, (float)y / height) != -1)
				put_p(map->img, x, y_offset + y, pick_color(ray, map, (float)y / height));
		}	
	}
}

void	get_textures(t_map *map)
{
	char		*wall_n;

	wall_n = "./textures/metal.xpm";
	map->wall_n.wall = mlx_xpm_file_to_image(&map->mlx, wall_n, &map->wall_n.wall_width, &map->wall_n.wall_height);
	map->wall_n.xpm_data.data = (int *)mlx_get_data_addr(map->wall_n.wall,
		&map->wall_n.xpm_data.bits_per_pixel, &map->wall_n.xpm_data.size_line,
		&map->wall_n.xpm_data.endian);
	char		*door;

	door = "./textures/42.xpm";
	map->door.wall = mlx_xpm_file_to_image(&map->mlx, door, &map->door.wall_width, &map->door.wall_height);
	map->door.xpm_data.data = (int *)mlx_get_data_addr(map->door.wall,
		&map->door.xpm_data.bits_per_pixel, &map->door.xpm_data.size_line,
		&map->door.xpm_data.endian);
}
