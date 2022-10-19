#include "cube3d.h"
#include <stdio.h>
#include "libmlx/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int		pick_color(t_ray ray, t_map *map, float percentage)
{
	int pixel_x;
	int pixel_y;
	t_wall wall;

	if (ray.side == 'n')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray.x) - ray.x);
		wall = map->wall_n;
	}
	if (ray.side == 's')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray.x) - ray.x);
		wall = map->wall_n;
	}
	if (ray.side == 'e')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray.y) - ray.y);
		wall = map->wall_n;
	}
	if (ray.side == 'w')
	{
		pixel_y = (int)(wall.wall_height * percentage); // how high and low the pixel is
		pixel_x = wall.wall_width * (ceil(ray.y) - ray.y);
		wall = map->wall_n;
	}

	// printf("%f\n", ray.len);
	// if (ray.len > 140)
		return (darken_rgb(wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y], ray.len));
	// return (wall.xpm_data.data[pixel_x + wall.wall_width * pixel_y]);
}

void	connect_dots_colors(t_map *map, int x, int height, t_ray ray)
{
	int	y;
	float y_offset;

	y = -1;
	ray.angle = 0;
	y_offset = 500 - (height / 2.5) - 0.01;
	while(y++ < height)
	{
		put_p(map->img, x, y_offset + y, pick_color(ray, map, (float)y / height));
	}
}

void	get_textures(t_map *map)
{
	char		*wall_n;

	wall_n = "./grass_chess.xpm";
	map->wall_n.wall = mlx_xpm_file_to_image(&map->mlx, wall_n, &map->wall_n.wall_width, &map->wall_n.wall_height);
	map->wall_n.xpm_data.data = (int *)mlx_get_data_addr(map->wall_n.wall,
		&map->wall_n.xpm_data.bits_per_pixel, &map->wall_n.xpm_data.size_line,
		&map->wall_n.xpm_data.endian);
}
