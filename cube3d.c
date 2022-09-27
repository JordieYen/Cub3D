/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/09/27 13:46:20 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
# include "libft/libft.h"
# include "libgnl/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include "libmlx/mlx.h"
#define BLK_WDT 32
#define STP_SZ 4
#define PI 3.14159265

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
	map->player->x = BLK_WDT / 2;
	map->player->y = BLK_WDT / 2;
	map->player->dx = cos(map->player->angle) * 5;
	map->player->dy = sin(map->player->angle) * 5;
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
			j++;
		}
		i++;
	}
	if (!check_walls(map))
		return (0);
	return (1);
}

void	put_p(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 1080 && x < 1920)
	{
		if (y > 0 && x > 0)
		{
			dst = data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

void	swapchar(char *one, char *two)
{
	char temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void	move_player_block(t_map *map, int key)
{
	int	x = map->player->xmap;
	int	y = map->player->ymap;
	
	if (key == S && map->coord[y + 1][x] == '0')
	{
		swapchar(&map->coord[y + 1][x], &map->coord[y][x]);
		map->player->y = 0;
	} 
	else if (key == W && map->coord[y - 1][x] == '0')
	{
		swapchar(&map->coord[y - 1][x], &map->coord[y][x]);
		map->player->y = BLK_WDT;
	}
	else if (key == D && map->coord[y][x + 1] == '0')
	{
		swapchar(&map->coord[y][x + 1], &map->coord[y][x]);
		map->player->x = 0;
	}
	else if (key == A && map->coord[y][x - 1] == '0')
	{
		swapchar(&map->coord[y][x - 1], &map->coord[y][x]);
		map->player->x = BLK_WDT;
	}
}

void move_player(t_map *map, int key)
{
	if (key == S)
	{
		if (map->coord[map->player->ymap + 1][map->player->xmap] == '0' || map->player->y < BLK_WDT - STP_SZ)
		{
			map->player->x -= map->player->dx;
			map->player->y -= map->player->dy;
		}
		if (map->player->y >= BLK_WDT)
			move_player_block(map, key);
	}
	if (key == W)
	{
		if (map->coord[map->player->ymap - 1][map->player->xmap] == '0' || map->player->y > 0 + STP_SZ)
		{
			map->player->x += map->player->dx;
			map->player->y += map->player->dy;
		}
		if (map->player->y <= 0)
			move_player_block(map, key);
	}
	if (key == D)
	{
		map->player->angle += 0.1;
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) * 5;
		map->player->dy = sin(map->player->angle) * 5;
	}
	if (key == A)
	{
		map->player->angle -= 0.1;
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) * 5;
		map->player->dy = sin(map->player->angle) * 5;
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


void	createScreen(t_map *map)
{
	t_data	img;

	img.img = mlx_new_image(map->mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	map->img = &img;

	int	y;
	int	j;
	int x;
	int color;
	int p;

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
			while (++p < BLK_WDT)
			{
				j = -1;
				while (++j < BLK_WDT)
					put_p(&img, x * BLK_WDT + p, y * BLK_WDT + j, color);
			}
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S' || map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->xmap = x;
				map->player->ymap = y;
				put_p(&img, (x * BLK_WDT) + map->player->x, (y * BLK_WDT) + map->player->y, 0xFFFF00);
				put_p(&img, (x * BLK_WDT) + map->player->x + 1, (y * BLK_WDT) + map->player->y, 0xFFFF00);
				put_p(&img, (x * BLK_WDT) + map->player->x, (y * BLK_WDT) + map->player->y - 1, 0xFFFF00);
				put_p(&img, (x * BLK_WDT) + map->player->x + 1, (y * BLK_WDT) + map->player->y - 1, 0xFFFF00);
				color = -1; //reuse this var to create dots for direction
				while (++color < 20)
				{
					put_p(&img, (x * BLK_WDT) + map->player->x + (map->player->dx * color / 4), (y * BLK_WDT) + map->player->y + (map->player->dy * color / 4), 0xFFFF00);	
				}
			}
			x++;
		}
		y++;
	}
	printf("PLAYER X: %d PLAYER Y: %d\n", map->player->x, map->player->y);
	mlx_put_image_to_window(map->mlx, map->win, img.img, 0, 0);
}

int	main(int argc, char **argv)
{
	int		fd;
	t_map	map;

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
		map.win = mlx_new_window(map.mlx, 1920, 1080, "FDF IS SO COOL");
		mlx_key_hook(map.win, deal_key, &map);
		createScreen(&map);
		mlx_loop(map.mlx);
	}
	else
		printf("input file name.");
	return (0);
}
