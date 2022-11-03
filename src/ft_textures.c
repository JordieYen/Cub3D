/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:54 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/11/02 19:59:06 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdio.h>
#include "../includes/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

t_wall	set_walls(t_map *map, t_ray *ray)
{
	t_wall	wall;

	if (ray->side == 'n')
		wall = map->wall_n;
	if (ray->side == 's')
		wall = map->wall_s;
	if (ray->side == 'e')
		wall = map->wall_e;
	if (ray->side == 'w')
		wall = map->wall_w;
	return (wall);
}

int	pick_color(t_ray *ray, t_map *map, float percentage)
{
	int		pixel_x;
	int		pixel_y;
	t_wall	wall;

	wall = set_walls(map, ray);
	if (ray->side == 'n' || ray->side == 's')
	{
		pixel_y = (int)(wall.wall_height * percentage);
		pixel_x = wall.wall_width * (ceil(ray->x) - ray->x);
	}
	if (ray->side == 'e' || ray->side == 'w')
	{
		pixel_y = (int)(wall.wall_height * percentage);
		pixel_x = wall.wall_width * (ceil(ray->y) - ray->y);
	}
	if ((unsigned int)wall.xpm_data.data[pixel_x
			+ wall.wall_width * pixel_y] == 4278190080)
		return (-1);
	return (darken_rgb(wall.xpm_data.data[pixel_x
				+ wall.wall_width * pixel_y], ray->len));
}

int	pick_color_door(t_ray *ray, t_map *map, float percentage)
{
	int		pixel_x;
	int		pixel_y;
	float	open;
	t_wall	wall;

	wall = map->door;
	if (ray->doorxmin == 0)
	{
		pixel_y = (int)(wall.wall_height * percentage);
		pixel_x = wall.wall_width * (ceil(ray->doorx) - ray->doorx);
		open = ceil(ray->doorx) - ray->doorx;
	}
	if (ray->doorxmin == 1)
	{
		pixel_y = (int)(wall.wall_height * percentage);
		pixel_x = wall.wall_width * (ceil(ray->doory) - ray->doory);
		open = ceil(ray->doory) - ray->doory;
	}
	if ((unsigned int)wall.xpm_data.data[pixel_x
			+ wall.wall_width * pixel_y] == 4278190080)
		return (-1);
	return (darken_rgb(wall.xpm_data.data[pixel_x
				+ wall.wall_width * pixel_y], ray->doorlen));
}

void	init_walls(t_map *map)
{
	get_xpm_data(map, &map->wall_n, map->tex->wall_no_dir);
	get_xpm_data(map, &map->wall_s, map->tex->wall_so_dir);
	get_xpm_data(map, &map->wall_e, map->tex->wall_ea_dir);
	get_xpm_data(map, &map->wall_w, map->tex->wall_we_dir);
	get_xpm_data(map, &map->door, map->tex->wall_do_dir);
	map->jump.wall = mlx_xpm_file_to_image(&map->mlx, "./textures/jump.xpm",
			&map->jump.wall_width, &map->jump.wall_height);
}

void	get_textures(t_map *map)
{
	map->hand = malloc(sizeof(t_wall) * 10);
	map->hand[0].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-1.xpm",
			&map->hand[0].wall_width, &map->hand[0].wall_height);
	map->hand[1].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-2.xpm",
			&map->hand[1].wall_width, &map->hand[1].wall_height);
	map->hand[2].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-3.xpm",
			&map->hand[2].wall_width, &map->hand[2].wall_height);
	map->hand[3].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-4.xpm",
			&map->hand[3].wall_width, &map->hand[3].wall_height);
	map->hand[4].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-5.xpm",
			&map->hand[4].wall_width, &map->hand[4].wall_height);
	map->hand[5].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-6.xpm",
			&map->hand[5].wall_width, &map->hand[5].wall_height);
	map->hand[6].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-7.xpm",
			&map->hand[6].wall_width, &map->hand[6].wall_height);
	map->hand[7].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-8.xpm",
			&map->hand[7].wall_width, &map->hand[7].wall_height);
	map->hand[8].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-9.xpm",
			&map->hand[8].wall_width, &map->hand[8].wall_height);
	map->hand[9].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/frame-0.xpm",
			&map->hand[9].wall_width, &map->hand[9].wall_height);
	map->knife.wall = mlx_xpm_file_to_image(&map->mlx, "./textures/knife.xpm",
			&map->knife.wall_width, &map->knife.wall_height);
	get_minecraft(map);
	init_walls(map);
}
