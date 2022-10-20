/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/20 12:47:26 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
# include "libft/libft.h"
# include "libgnl/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include "libmlx/mlx.h"
# include <float.h>
# include <stdbool.h>
# include <stdlib.h>

void	init_map(t_map *map, int fd)
{
	int		x;
	int		y;
	char	*line;

	line = get_next_line(fd);
	x = 0;
	y = 0;
	while (line != NULL)
	{
		if (ft_strlen(line) > x)
			x = ft_strlen(line);
		y++;
		free(line);
		line = get_next_line(fd);
	}
	map->xlen = x - 1;
	map->ylen = y;
	if (y > 0)
		map->coord = malloc((y + 1) * sizeof(char *));
	while (y >= 0)
	{
		map->coord[y] = malloc((x + 1) * sizeof(char));
		y--;
	}
	map->player = malloc(sizeof(t_player));
	map->player->angle = 4.71239;
	map->player->dx = cos(map->player->angle) / 10;
	map->player->dy = sin(map->player->angle) / 10;
}

void	fill_map(t_map *map, int fd)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	while (i < map->ylen)
	{
		j = 0;
		line = get_next_line(fd);
		while (j < map->xlen + 2)
		{
			if (j < ft_strlen(line) - 1)
				map->coord[i][j] = line[j];
			else
				map->coord[i][j] = ' ';
			if (j == map->xlen + 1)
				map->coord[i][j] = '\0';
			j++;
		}
		free(line);
		i++;
	}
	map->coord[i] = NULL;
}

void	print_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->ylen)
	{
		j = 0;
		while (j < map->xlen)
		{
			printf("%c", map->coord[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
}

int	check_space(t_map *map, int x, int y)
{
	if (map->coord[y + 1] != NULL)
	{
		if (map->coord[y + 1][x] != ' ' && map->coord[y + 1][x] != '1')
			return (0);
	}
	if (y != 0)
	{
		if (map->coord[y - 1][x] != ' ' && map->coord[y - 1][x] != '1')
			return (0);
	}
	if (map->coord[y][x + 1] != '\0')
	{
		if (map->coord[y][x + 1] != ' ' && map->coord[y][x + 1] != '1')
			return (0);
	}
	if (x != 0)
	{
		if (map->coord[y][x - 1] != ' ' && map->coord[y][x - 1] != '1')
			return (0);
	}
	return (1);
}

int	check_walls(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->coord[i] != NULL)
	{
		j = 0;
		while (map->coord[i][j] != '\0')
		{
			if (map->coord[i][j] == ' ')
			{
				if (!check_space(map, j, i))
					return (0);
			}
			if ((i == 0 || map->coord[i + 1] == 0) && (map->coord[i][j]
				!= ' ' && map->coord[i][j] != '1'))
				return (0);
			else if ((j == 0 || map->coord[i][j + 1] == '\0')
				&& (map->coord[i][j] != ' ' && map->coord[i][j] != '1'))
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

int	check_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (map->coord[i] != NULL)
	{
		j = 0;
		while (map->coord[i][j] != '\0')
		{
			if (map->coord[i][j] != '0' && map->coord[i][j] != '1'
				&& map->coord[i][j] != ' ' && map->coord[i][j] != 'N'
				&& map->coord[i][j] != 'S' && map->coord[i][j] != 'E'
				&& map->coord[i][j] != 'W')
				return (0);
			else if (map->coord[i][j] != 'N'
				&& map->coord[i][j] != 'S' && map->coord[i][j] != 'E'
				&& map->coord[i][j] != 'W')
				map->direction = map->coord[i][j];
			j++;
		}
		i++;
	}
	if (!check_walls(map))
		return (0);
	return (1);
}

//TODO: dont move player at all if it will touch a wall on any side
void move_player(t_map *map, int key)
{
	if (key == S)
	{
		if (map->coord[(int)(map->player->y - map->player->dy)][(int)(map->player->x  - map->player->dx)] == '0')
		{
			map->player->x -= map->player->dx;
			map->player->y -= map->player->dy;
		}
	}
	if (key == W)
	{
		if (map->coord[(int)(map->player->y + map->player->dy)][(int)(map->player->x  + map->player->dx)] == '0')
		{
			map->player->x += map->player->dx;
			map->player->y += map->player->dy;
		}
	}
	if (key == D)
	{
		map->player->angle += DR * 9;
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	if (key == A)
	{
		map->player->angle -= DR * 9;
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
}

void	createScreen(t_map *map);


int	deal_key(int key, t_map *map)
{
	if (key == W || key == A || key == S || key == D)
	{
		move_player(map, key);
		mlx_clear_window(map->mlx, map->win);
		createScreen(map);
	}
	return (0);
}

void	draw_rays(t_map *map)
{
	int		ray_num;
	int		i;
	int		j;
	int		xmin;
	float	DistT;
	float	angle;
	float	lineH;
	int		dof_max;
	t_fcoord ray_max;
	t_fcoord ray_dir;
	t_coord	map_check;
	t_fcoord ray_step_size;
	t_fcoord ray_length_1d;
	t_fcoord step;
	t_fcoord ray_start;
	float		dy;
	float		dx;
	int		magnitude;

	dof_max = 12;
	ray_num = 1920;
	map->rays = malloc(sizeof(t_ray) * ray_num);

	i = -1;
	angle = (map->player->angle) - (DR/21.333 * (ray_num/2));
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	while (++i < ray_num)
	{
		dx = cos(angle) / 10;
		dy = sin(angle) / 10;
		ray_start.x = map->player->x;
		ray_start.y = map->player->y;
		ray_max.x = ((map->player->x) + (dx * 2000));
		ray_max.y = ((map->player->y) + (dy * 2000));
		ray_dir.x = ray_max.x - map->player->x;
		ray_dir.y = ray_max.y - map->player->y;
		magnitude = dist(ray_max.x, ray_max.y,  map->player->x,  map->player->y);
		ray_dir.x = ray_dir.x / magnitude;
		ray_dir.y = ray_dir.y / magnitude;
		ray_step_size.x = sqrt(1 + (ray_dir.y / ray_dir.x) * (ray_dir.y / ray_dir.x));
		ray_step_size.y = sqrt(1 + (ray_dir.x / ray_dir.y) * (ray_dir.x / ray_dir.y));
		map_check.x = map->player->x;
		map_check.y = map->player->y;

		// Establish Starting Conditions
		if (ray_dir.x < 0)
		{
			step.x = -1;
			ray_length_1d.x = (ray_start.x - (float)map_check.x) * ray_step_size.x;
		}
		else
		{
			step.x = 1;
			ray_length_1d.x = ((float)map_check.x + 1 - ray_start.x) * ray_step_size.x;
		}

		if (ray_dir.y < 0)
		{
			step.y = -1;
			ray_length_1d.y = (ray_start.y - (float)map_check.y) * ray_step_size.y;
		}
		else
		{
			step.y = 1;
			ray_length_1d.y = ((float)map_check.y + 1 - ray_start.y) * ray_step_size.y;
		}
		bool bTileFound = false;
		float fMaxDistance = 2000.0f;
		float fDistance = 0.0f;

		while (!bTileFound && fDistance < fMaxDistance)
		{
			// Walk along shortest path
			if (ray_length_1d.x < ray_length_1d.y)
			{
				map_check.x += step.x;
				fDistance = ray_length_1d.x;
				ray_length_1d.x += ray_step_size.x;
				xmin = 1;
			}
			else
			{
				map_check.y += step.y;
				fDistance = ray_length_1d.y;
				ray_length_1d.y += ray_step_size.y;
				xmin = 0;
			}
			// Test tile at new test point
			if (map_check.x >= 0 && map_check.x < map->xlen && map_check.y >= 0 && map_check.y < map->ylen)
			{
				if (map->coord[map_check.y][map_check.x] == '1')
					bTileFound = true;
			}
		}
		// Calculate intersection location
		if (bTileFound)
		{
			map->rays[i].x = (ray_start.x + ray_dir.x * fDistance);
			map->rays[i].y = (ray_start.y + ray_dir.y * fDistance);
			if (xmin == 0 && angle > 0 && angle < PI)
				map->rays[i].side = 'n';
			else if (xmin == 0 && angle > PI && angle < 2 * PI)
				map->rays[i].side = 's';
			if (xmin == 1 && angle < P3 && angle > P2)
				map->rays[i].side = 'w';
			else if (xmin == 1 && (angle < P2 || angle > P3))
				map->rays[i].side = 'e';
			DistT = fDistance * BLK_WDT_PXL;
		}
		
		float ca = map->player->angle - angle;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		if (DistT != -1)
			DistT = DistT * cos(ca);
		map->rays[i].len = DistT;
		angle += DR/21.3333;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;

		//Calculate height of line to draw on screen
	}
	// draw_2d_rays(map, ray_num);
	// print 3d map
	// create_line_colors(map, ray_num);
	// int	color;
	// i = -1;
	// while (++i < ray_num)
	// {
		j = -1;
	// 	color = 0xFFFFFF;
	// 	while (j++ < 1080)
	// 	{
	// 		put_p(map->img, i, j, color);
	// 		if (j < 504 && j > 300 && color - 0x010101 > 0)
	// 			color = color - 0x010101;
	// 		if (j > 504 && j < 700  && color + 0x010101 < 0xFFFFFF)
	// 			color = color + 0x010101;
	// 		// if (i == 0)
	// 		// 	printf("color = %d\n", color);
	// 	}
	// }
	i = -1;
	while (++i < ray_num)
	{
		lineH = (40 * 800) / map->rays[i].len + 0.01;
		connect_dots_colors(map, i, lineH, map->rays[i]);
	}
	free(map->rays);
}

void	createScreen(t_map *map)
{
	int	y;
	int	j;
	int x;
	int color;
	int p;
	t_data img;

	// mlx_destroy_image(map->mlx, map->img);
	img.img = mlx_new_image(map->mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
	map->img = &img;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			if (map->coord[y][x] == '1')
				color = 0x0066B2FF;
			else if (map->coord[y][x] == ' ')
				color = 0x00000;
			else
				color = 0xFF4500;
			p = -1;
			// while (++p < BLK_WDT_PXL - 1)
			// {
				j = -1;
			// 	while (++j < BLK_WDT_PXL - 1)
			// 		put_p(map->img, x * BLK_WDT_PXL + p, y * BLK_WDT_PXL + j, color);
			// }
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S' || map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->x = x + 0.5;
				map->player->y = y + 0.5;
				map->coord[y][x] = '0';
			}
			// if (y + 1 == map->ylen && x + 1 == map->xlen)
			// {
			// 	put_p(map->img, (map->player->x * BLK_WDT_PXL), (map->player->y * BLK_WDT_PXL), 0xFFFF00);
			// 	put_p(map->img, (map->player->x * BLK_WDT_PXL) + 1, (map->player->y * BLK_WDT_PXL), 0xFFFF00);
			// 	put_p(map->img, (map->player->x * BLK_WDT_PXL), (map->player->y * BLK_WDT_PXL) - 1, 0xFFFF00);
			// 	put_p(map->img, (map->player->x * BLK_WDT_PXL) + 1, (map->player->y * BLK_WDT_PXL) - 1, 0xFFFF00);
			// 	color = -1; //reuse this var to create dots for direction
			// 	while (++color < 20)
			// 		put_p(map->img, (map->player->x * BLK_WDT_PXL) + (map->player->dx * color * 10), (map->player->y * BLK_WDT_PXL) + (map->player->dy * color * 10), 0xFFFF00);
			// }
			// put_p(map->img, (map->player->x * BLK_WDT_PXL) + (map->player->dx * 2000), (map->player->y * BLK_WDT_PXL) + (map->player->dy * 2000), 0xFFFF00);
			x++;
		}
		y++;
	}
	draw_rays(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	map;
	t_data	img;

	if (argc == 2)
	{
		fd = open(argv[1], O_RDONLY);
		init_map(&map, fd);
		close(fd);
		fd = open(argv[1], O_RDONLY);
		fill_map(&map, fd);
		if (check_map(&map))
			print_map(&map);
		else
			printf("invalid map\n");
		printf("\n xlen = %d, ylen = %d\n", map.xlen, map.ylen);
		map.mlx = mlx_init();
		map.win = mlx_new_window(map.mlx, 1920, 1080, "MLX CUBE3D");
		img.img = mlx_new_image(map.mlx, 1920, 1080);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		map.img = &img;
		get_textures(&map);
		mlx_hook(map.win, 2, 0, deal_key, &map);
		createScreen(&map);
		mlx_loop(map.mlx);
	}
	else
		printf("input file name.");
	return (0);
}
