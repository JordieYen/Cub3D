/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 20:28:03 by jking-ye         ###   ########.fr       */
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

void	create_creen(t_map *map);

void	draw_player(t_map *map, int x, int y)
{
	int	color;

	color = 0xAF133D;
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
			y + (map->player->dy * color * 10), 0xAF133D);
}

void	render_minimap(t_map *map, int start_x, int start_y, int size)
{
	int		x;
	int		y;
	float	tempx;
	float	tempy;
	int		color;

	y = start_y - 1;
	tempy = map->player->y - 3;
	while (y++ < start_y + size - start_x)
	{
		tempx = map->player->x - 3;
		x = start_x - 1;
		while (x++ < start_x + size - start_x)
		{
			put_p(map->img, x, y, 0);
			if ((tempx > 0 && tempx < map->xlen)
				&& (tempy > 0 && tempy < map->ylen))
			{
				if (map->coord[(int)tempy][(int)tempx] == '1')
					color = 0x61061F;
				else if (map->coord[(int)tempy][(int)tempx] == 'C')
					color = 0x61061F;
				else
					color = 0;
				put_p(map->img, x, y, color);
			}
			tempx += 0.03125;
		}
		tempy += 0.03125;
	}
	draw_player(map, start_x + (size / 2) - 15, start_y + (size / 2) - 15);
}

void	draw_minimap(t_map *map)
{
	int	x;
	int	y;
	int	size;

	size = 224;
	y = WIN_H - size - 1;
	render_minimap(map, 30, WIN_H - size, size);
	while (y++ < WIN_H - 30)
	{
		x = 29;
		while (x++ < size)
		{
			if (y <= WIN_H - size + 1 || x <= 31
				|| y >= WIN_H - 31 || x >= size - 1)
				put_p(map->img, x, y, 0x44101E);
		}
	}
}

void	shoot_rays(t_map *map)
{
	int			i;
	float		angle;
	t_coord		map_check;
	t_fcoord	step;
	t_ray		*ray;

	map->rays = malloc(sizeof(t_ray *) * WIN_W);
	angle = (map->player->angle) - (DR / 16 * (WIN_W / 2));
	if (angle < 0)
		angle += 2 * PI;
	else if (angle > 2 * PI)
		angle -= 2 * PI;
	i = -1;
	while (++i < WIN_W)
	{
		map->rays[i] = init_ray(angle, map);
		ray = map->rays[i];
		init_map_check_ray_dir(ray, &map_check, map, &step);
		calculate_intersection(ray,
			walk_shortest_path(ray, &map_check, &step, map));
		angle = rotate_angle(angle);
	}
}

void	create_creen(t_map *map)
{
	int	y;
	int	x;

	y = -1;
	while (++y < map->ylen)
	{
		x = -1;
		while (++x < map->xlen)
		{
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S'
				|| map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->x = x + 0.5;
				map->player->y = y + 0.5;
				map->coord[y][x] = '0';
			}
		}
	}
	shoot_rays(map);
	render_background(map, WIN_W);
	render_rays(map, WIN_W);
	render_doors(map, WIN_W);
	draw_minimap(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	x = -1;
	while (++x < WIN_W)
		free(map->rays[x]);
	free(map->rays);
}

t_wall	changeframe(t_map *map)
{
	static int	i;
	static int	direction;
	t_wall		frame;

	frame = map->hand[i];
	if (direction == 0 && map->equipweapon == 1)
	{
		if (i < 9)
			i++;
		else
			direction = 1;
	}
	else if (direction == 1 && map->equipweapon == 2)
	{
		if (i > 0)
			i--;
		else
			direction = 0;
	}
	return (frame);
}

void	animatehand(t_map *map)
{
	static int	i;
	static int	direction;
	t_wall		frame;

	frame = changeframe(map);
	if (map->swapweapon == 1)
		mlx_put_image_to_window(map->mlx, map->win, frame.wall,
			WIN_W - frame.wall_width, WIN_H - frame.wall_height + (i * 2));
	else
		mlx_put_image_to_window(map->mlx, map->win, map->knife.wall, WIN_W
			- map->knife.wall_width, WIN_H - map->knife.wall_height + (i * 2));
	if (direction == 0)
	{
		if (i < 20)
			i++;
		else
			direction = 1;
	}
	else
	{
		if (i > 0)
			i--;
		else
			direction = 0;
	}
	map->offset = i;
}

int	render_screen(void *varg)
{
	t_map			*map;
	struct timeval	tv;
	int				color;
	char			*fps_str;
	char			*fps_num;

	gettimeofday(&tv, NULL);
	map = (t_map *) varg;
	mlx_clear_window(map->mlx, map->win);
	create_creen(map);
	animatehand(map);
	map->fps = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - map->last_frame;
	map->last_frame = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	color = 0xFFFFFF;
	if (1000 / map->fps >= 20)
		color = 0x00FF00;
	if (1000 / map->fps < 20)
		color = 0xFFFF00;
	if (1000 / map->fps < 10)
		color = 0xFF0000;
	fps_num = ft_itoa((float) 1000 / map->fps);
	fps_str = ft_strjoin("fps :", fps_num);
	mlx_string_put(map->mlx, map->win, 0, 0, color, fps_str);
	free(fps_num);
	free(fps_str);
	return (0);
}

int	main(int argc, char **argv)
{
	t_map	*map;
	t_data	img;

	map = malloc(sizeof(t_map));
	if (argc == 2 && check_cub(map, argv[1]))
	{
		map->mlx = mlx_init();
		map->win = mlx_new_window(map->mlx, WIN_W, WIN_H, "MLX CUBE3D");
		img.img = mlx_new_image(map->mlx, WIN_W, WIN_H);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		map->img = &img;
		get_textures(map);
		create_creen(map);
		map->last_frame = 0;
		mlx_hook(map->win, 2, 0, deal_key, map);
		mlx_hook(map->win, 6, 0, read_mouse, map);
		mlx_loop_hook(map->mlx, render_screen, map);
		mlx_mouse_move(map->win, 100, 100);
		mlx_mouse_hide(map->mlx, map->win);
		mlx_loop(map->mlx);
	}
	return (0);
}
