/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/23 02:05:20 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
# include "libft/libft.h"
# include "libgnl/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include "libmlx/mlx.h"
# include <float.h>
# include <stdlib.h>
# include <sys/time.h>

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
		map->player->angle += DR * 3;
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	if (key == A)
	{
		map->player->angle -= DR * 3;
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
		move_player(map, key);
	return (0);
}

void	draw_minimap(t_map *map)
{
	int	x;
	int	y;
	int	size;

	size = 250;
	y = WIN_H - size - 1;
	while (y++ <  WIN_H - 30)
	{
		x = 29;
		while (x++ < size)
		{
			if (y == WIN_H - size || x == 30 || y == WIN_H - 30 || x == size)
				put_p(map->img, x, y, -1);
			// if (y == WIN_H - (size * 1.5) )
		}
	}
	put_p(map->img, x, y, 0x0);
}

void	shoot_rays(t_map *map)
{
	int			i;
	float		angle;
	t_coord		map_check;
	t_fcoord	step;
	t_ray		*ray;

	map->rays = malloc(sizeof(t_ray) * WIN_W);
	angle = (map->player->angle) - (DR/21.333 * (WIN_W/2));
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
		calculate_intersection(ray, walk_shortest_path(ray, &map_check, &step, map));
		angle = rotate_angle(angle);
	}

}

void	createScreen(t_map *map)
{
	int	y;
	int x;
	t_data img;

	img.img = mlx_new_image(map->mlx, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
	map->img = &img;
	y = 0;
	while (y < map->ylen)
	{
		x = 0;
		while (x < map->xlen)
		{
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S' || map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->x = x + 0.5;
				map->player->y = y + 0.5;
				map->coord[y][x] = '0';
			}
			x++;
		}
		y++;
	}
	shoot_rays(map);
	render_background(map, WIN_W);
	render_rays(map, WIN_W);
	draw_minimap(map);
	mlx_put_image_to_window(map->mlx, map->win, map->img->img, 0, 0);
	x = -1;
	while (++x < WIN_W)
		free(map->rays[x]);
	free(map->rays);
}

int	render_screen(void *varg)
{
	t_map *map;
	struct timeval tv;
	int	color;

	gettimeofday(&tv, NULL);
	map = (t_map *) varg;
	mlx_clear_window(map->mlx, map->win);
	createScreen(map);
	map->fps = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - map->last_frame;
	map->last_frame = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	color = 0xFFFFFF;
	if (1000 / map->fps >= 20)
		color = 0x00FF00;
	if (1000 / map->fps < 20)
		color = 0xFFFF00;
	if (1000 / map->fps < 10)
		color = 0xFF0000;

	mlx_string_put(map->mlx, map->win, 0 ,0, color, ft_strjoin("fps :",ft_itoa((float) 1000 / map->fps)));
	return 0;
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
		if (check_map(&map) != 1)
			printf("invalid map\n");
		map.mlx = mlx_init();
		map.win = mlx_new_window(map.mlx, WIN_W, WIN_H, "MLX CUBE3D");
		img.img = mlx_new_image(map.mlx, WIN_W, WIN_H);
		img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
				&img.line_length, &img.endian);
		map.img = &img;
		get_textures(&map);
		createScreen(&map);
		map.last_frame = 0;
		mlx_hook(map.win, 2, 0, deal_key, &map);
		mlx_loop_hook(map.mlx, render_screen, &map);
		mlx_loop(map.mlx);
	}
	else
		printf("input file name.");
	return (0);
}
