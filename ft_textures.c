/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:54 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/27 13:33:42 by jking-ye         ###   ########.fr       */
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
		wall = map->wall_s;
	if (ray->side == 'e')
		wall = map->wall_e;
	if (ray->side == 'w')
		wall = map->wall_w;


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
				put_p(map->img, x, y_offset + y + map->offset, pick_color_door(ray, map, (float)y / height));
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
	while(y++ < height - 1)
	{
		if (y_offset + y > 0 && y_offset + y < WIN_H)
		{
			if (pick_color(ray, map, (float)y / height) != -1)
				put_p(map->img, x, y_offset + y + map->offset, pick_color(ray, map, (float)y / height));
		}	
	}
}

void	get_xpm_data(t_map *map, t_wall *wall, char *texture)
{	
	wall->wall = mlx_xpm_file_to_image(&map->mlx, texture, &wall->wall_width, &wall->wall_height);
	wall->xpm_data.data = (int *)mlx_get_data_addr(wall->wall,
		&wall->xpm_data.bits_per_pixel, &wall->xpm_data.size_line,
		&wall->xpm_data.endian);
}

void	get_textures(t_map *map)
{
	map->hand = malloc(sizeof(t_wall) * 10);
	map->hand[0].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-1-new-removebg-preview.xpm", &map->hand[0].wall_width, &map->hand[0].wall_height);
	map->hand[1].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-2-new-removebg-preview.xpm", &map->hand[1].wall_width, &map->hand[1].wall_height);
	map->hand[2].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-3-new-removebg-preview.xpm", &map->hand[2].wall_width, &map->hand[2].wall_height);
	map->hand[3].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-4-new-removebg-preview.xpm", &map->hand[3].wall_width, &map->hand[3].wall_height);
	map->hand[4].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-5-new-removebg-preview.xpm", &map->hand[4].wall_width, &map->hand[4].wall_height);
	map->hand[5].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-6-new-removebg-preview.xpm", &map->hand[5].wall_width, &map->hand[5].wall_height);
	map->hand[6].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-7-new-removebg-preview.xpm", &map->hand[6].wall_width, &map->hand[6].wall_height);
	map->hand[7].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-8-new-removebg-preview.xpm", &map->hand[7].wall_width, &map->hand[7].wall_height);
	map->hand[8].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-9-new-removebg-preview.xpm", &map->hand[8].wall_width, &map->hand[8].wall_height);
	map->hand[9].wall = mlx_xpm_file_to_image(&map->mlx, "./sprite-frames/AnyConv.com__frame-10-new-removebg-preview.xpm", &map->hand[9].wall_width, &map->hand[9].wall_height);
	map->knife.wall = mlx_xpm_file_to_image(&map->mlx, "./right-knife.xpm", &map->knife.wall_width, &map->knife.wall_height);
	get_xpm_data(map, &map->wall_n, map->tex->wall_no_dir);
	get_xpm_data(map, &map->wall_s, map->tex->wall_so_dir);
	get_xpm_data(map, &map->wall_e, map->tex->wall_ea_dir);
	get_xpm_data(map, &map->wall_w, map->tex->wall_we_dir);
	get_xpm_data(map, &map->door, map->tex->wall_do_dir);
}
