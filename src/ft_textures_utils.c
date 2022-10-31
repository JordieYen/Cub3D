/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_textures_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 12:37:37 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/31 19:21:12 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdio.h>
#include "../includes/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>
#include "../includes/libft.h"

void	get_xpm_data(t_map *map, t_wall *wall, char *texture)
{	
	wall->wall = mlx_xpm_file_to_image(&map->mlx, texture,
			&wall->wall_width, &wall->wall_height);
	wall->xpm_data.data = (int *)mlx_get_data_addr(wall->wall,
			&wall->xpm_data.bits_per_pixel, &wall->xpm_data.size_line,
			&wall->xpm_data.endian);
}

void	connect_dots_colors(t_map *map, int x, int height, t_ray *ray)
{
	int		y;
	float	y_offset;

	y = -1;
	ray->angle = 0;
	y_offset = 400 - (height / 2.5) - 0.01;
	while (y++ < height - 1)
	{
		if (y_offset + y > 0 && y_offset + y < 810)
		{
			if (pick_color(ray, map, (float)y / height) != -1)
				put_p(map->img, x, y_offset + y + map->offset,
					pick_color(ray, map, (float)y / height));
		}	
	}
}

void	connect_dots_doors(t_map *map, int x, int height, t_ray *ray)
{
	int		y;
	float	y_offset;

	y = -1;
	y_offset = 400 - (height / 2.5) - 0.01;
	while (y++ < height - 1)
	{
		if (y_offset + y > 0 && y_offset + y < 810)
		{
			if (pick_color_door(ray, map, (float)y / height) != -1)
				put_p(map->img, x, y_offset + y + map->offset,
					pick_color_door(ray, map, (float)y / height));
		}	
	}
}

int	init_texture_color(t_map *map, char *line)
{
	if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
		|| !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
		|| !ft_strncmp(line, "DO", 2))
		init_texture(map, line);
	else if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
		init_color(map, line);
	else if (ft_strncmp(line, "\n", 1))
	{
		ft_putstr_fd("Error: bad key\n", 2);
		system("leaks cub3D");
		exit(0);
	}
	return (1);
}
