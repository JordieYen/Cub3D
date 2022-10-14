/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 14:34:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/14 20:35:23 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
# include "libft/libft.h"
# include "libgnl/get_next_line.h"
# include <stdio.h>
# include <math.h>
# include "libmlx/mlx.h"
# include <float.h>

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
	map->player->angle = 4.71239;
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

void	swapchar(char *one, char *two)
{
	char temp;

	temp = *one;
	*one = *two;
	*two = temp;
}

void	move_player_block(t_map *map)
{
	int	x = map->player->xmap;
	int	y = map->player->ymap;
	
	if (map->player->y < 0)
	{
		if (map->coord[y - 1][x] == '0')
		{
			swapchar(&map->coord[y - 1][x], &map->coord[y][x]);
			map->player->y = BLK_WDT;
		}
		else
		{
			if (round(map->player->dy) > STP_SZ)
				map->player->y += round(map->player->dy);
			else
				map->player->y += STP_SZ;
		}
	} 
	else if (map->player->y > BLK_WDT)
	{
		if (map->coord[y + 1][x] == '0')
		{
			swapchar(&map->coord[y + 1][x], &map->coord[y][x]);
			map->player->y = 0;
		}
		else
		{
			if (round(map->player->dy) > STP_SZ)
				map->player->y -= round(map->player->dy);
			else
				map->player->y -= STP_SZ;
		}
	}
	else if (map->player->x > BLK_WDT)
	{
		if (map->coord[y][x + 1] == '0')
		{
			swapchar(&map->coord[y][x + 1], &map->coord[y][x]);
			map->player->x = 0;
		}
		else
		{
			if (round(map->player->dx) > STP_SZ)
				map->player->x -= round(map->player->dx);
			else
				map->player->x -= STP_SZ;
		}
	}
	else if (map->player->x < 0)
	{
		if (map->coord[y][x - 1] == '0')
		{
			swapchar(&map->coord[y][x - 1], &map->coord[y][x]);
			map->player->x = BLK_WDT;
		}
		else
		{
			if (round(map->player->dx) > STP_SZ)
				map->player->x += round(map->player->dx);
			else
				map->player->x += STP_SZ;
		}
		
	}
}

//TODO: dont move player at all if it will touch a wall on any side
void move_player(t_map *map, int key)
{
	if (key == S)
	{
		if ((map->coord[map->player->ymap + 1][map->player->xmap] == '0' || map->player->y <= BLK_WDT - STP_SZ) && (map->coord[map->player->ymap][map->player->xmap + 1] == '0' || map->player->x <= BLK_WDT - STP_SZ))
		{
			map->player->x -= round(map->player->dx);
			map->player->y -= round(map->player->dy);
		}
		if (map->player->y >= BLK_WDT || map->player->y <= 0 || map->player->x >= BLK_WDT || map->player->x <= 0)
			move_player_block(map);
	}
	if (key == W)
	{
		if ((map->coord[map->player->ymap - 1][map->player->xmap] == '0' || map->player->y >= 0 + STP_SZ) && (map->coord[map->player->ymap][map->player->xmap - 1] == '0' || map->player->x >= 0 + STP_SZ))
		{
			map->player->x += round(map->player->dx);
			map->player->y += round(map->player->dy);
		}
		if (map->player->y >= BLK_WDT || map->player->y <= 0 || map->player->x >= BLK_WDT || map->player->x <= 0)
			move_player_block(map);
	}
	if (key == D)
	{
		map->player->angle += DR * 4;
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) * 4;
		map->player->dy = sin(map->player->angle) * 4;
	}
	if (key == A)
	{
		map->player->angle -= DR * 4;
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) * 4;
		map->player->dy = sin(map->player->angle) * 4;
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
	// t_data	*img;
	int		ray_num;
	int		dof;
	int		xoff;
	int		yoff;
	int		mapy;
	int		mapx;
	float	aTan;
	float	nTan;
	int		i;
	int		j;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	float	DistH;
	float	DistV;
	float	DistT;
	t_coord	coord1;
	t_coord	coord2;
	float	angle;
	float	lineH;
	float	lineO;
	int		dof_max;

	dof_max = 12;
	ray_num = 1980;
	map->rays = malloc(sizeof(t_ray) * ray_num);

	i = -1;
	angle = (map->player->angle) - (DR/21 * (ray_num/2));
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	while (++i < ray_num)
	{
		DistH = 1000000;
		DistV = 1000000; 
		hx = map->player->x;
		hy = map->player->y;
		// -- checking horizontal line --
		dof = 0;
		aTan = -1/tan(angle);
		if (angle > PI) //if player facing upwards
		{
			map->rays[i].y = ((((int)((map->player->ymap * BLK_WDT) + map->player->y)>>6)<<6) - 0.0001);
			map->rays[i].x = ((map->player->ymap * BLK_WDT ) + map->player->y - map->rays[i].y) * aTan + (map->player->xmap * BLK_WDT + map->player->x);
			yoff = - BLK_WDT;
			xoff = -yoff * aTan;
		}
		if (angle < PI) //if player facing downdwards
		{
			map->rays[i].y = ((((int)((map->player->ymap * BLK_WDT) + map->player->y)>>6)<<6) + BLK_WDT);
			map->rays[i].x = ((map->player->ymap * BLK_WDT ) + map->player->y - map->rays[i].y) * aTan + (map->player->xmap * BLK_WDT + map->player->x);
			yoff = BLK_WDT;
			xoff = -yoff * aTan;
		}
		if (angle == 0 || angle == PI) //if player facing straight, left or down
		{
			map->rays[i].x = map->player->x;
			map->rays[i].y = map->player->y;
			dof = dof_max;
			printf("THIS RAY %d\n", i);
		}
		while (dof++ < dof_max)
		{
			mapx = ((int)map->rays[i].x >> 6);
			mapy = ((int)map->rays[i].y >> 6);

			if (mapx < 0)
				mapx = 0;
			if (mapy < 0)
				mapy = 0;
			if ((mapy < map->ylen && mapx < map->xlen) &&  (map->coord[mapy][mapx] == '1'))
			{
				hx = map->rays[i].x;
				hy = map->rays[i].y;
				DistH = dist((map->player->xmap * BLK_WDT + map->player->x), (map->player->ymap * BLK_WDT + map->player->y), hx, hy);
				dof = dof_max;
			}
			else
			{
				map->rays[i].x += xoff;
				map->rays[i].y += yoff;
			}
		}
		// -- checking vertical line --
		dof = 0;
		vx = map->player->x;
		vy = map->player->y;
		nTan = -tan(angle);
		if (angle > P2 && angle < P3) //if player facing leftwards
		{
			map->rays[i].x = ((((int)((map->player->xmap * BLK_WDT) + map->player->x)>>6)<<6) - 0.0001);
			map->rays[i].y = ((map->player->xmap * BLK_WDT ) + map->player->x - map->rays[i].x) * nTan + (map->player->ymap * BLK_WDT + map->player->y);
			xoff = - BLK_WDT;
			yoff = -xoff * nTan;
		}
		if (angle < P2 || angle > P3) //if player facing rightwards
		{
			map->rays[i].x = ((((int)((map->player->xmap * BLK_WDT) + map->player->x)>>6)<<6) + BLK_WDT);
			map->rays[i].y = ((map->player->xmap * BLK_WDT ) + map->player->x - map->rays[i].x) * nTan + (map->player->ymap * BLK_WDT + map->player->y);
			xoff = BLK_WDT;
			yoff = -xoff * nTan;
		}
		if (angle == 0 || angle == PI) //if player facing exactly up or down
		{
			map->rays[i].x = map->player->x;
			map->rays[i].y = map->player->y;
			dof = dof_max;
		}
		while (dof++ < dof_max)
		{
			mapx = ((int)map->rays[i].x >> 6);
			mapy = ((int)map->rays[i].y >> 6);

			if (mapx < 0)
				mapx = 0;
			if (mapy < 0)
				mapy = 0;
			if ((mapy < map->ylen && mapx < map->xlen) &&  (map->coord[mapy][mapx] == '1'))
			{
				vx = map->rays[i].x;
				vy = map->rays[i].y;
				DistV = dist((map->player->xmap * BLK_WDT + map->player->x), (map->player->ymap * BLK_WDT + map->player->y), vx, vy);
				dof = dof_max;
			}
			else
			{
				map->rays[i].x += xoff;
				map->rays[i].y += yoff;
			}
		}
		if (DistH == 1000000 && DistV == 1000000)
			DistT = -1;

		map->rays[i].up = 0;
		map->rays[i].left = 0;
		map->rays[i].xmin = 0;
		if (DistH < DistV)
		{
			map->rays[i].xmin = 1;
			if (angle > P3 && angle < P2)
				map->rays[i].up = 0;
			else
				map->rays[i].up = 1;
			map->rays[i].x = hx;
			map->rays[i].y = hy;
			DistT = DistH;
		}
		else if (DistH > DistV)
		{
			map->rays[i].xmin = 0;
			if (angle > PI && angle < 2 * PI)
				map->rays[i].left = 0;
			else
				map->rays[i].left = 1;
			map->rays[i].x = vx;
			map->rays[i].y = vy;
			DistT = DistV;
		}

		float ca = map->player->angle - angle;
		if (ca < 0)
			ca += 2 * PI;
		if (ca > 2 * PI)
			ca -= 2 * PI;
		if (DistT != -1)
			DistT = DistT * cos(ca);
		map->rays[i].len = DistT;
		angle += DR/21;
		if (angle < 0)
			angle += 2 * PI;
		if (angle > 2 * PI)
			angle -= 2 * PI;	
	}
	draw_2d_rays(map, ray_num);

	// corner fix
	i = -1;
	j = 0;
	while (++i < ray_num)
	{
		j = 0;
		if (map->rays[i].len - map->rays[i + 1].len < -20)
		{
			j = 1;
			while (map->rays[i].len - map->rays[i + j].len < -20 && (map->rays[i + j].len - map->rays[i + j + 1].len > -5 && map->rays[i + j].len - map->rays[i + j + 1].len < 5))
				j++;
		}
		if ((map->rays[i].len - map->rays[i + j + 1].len > -5 && map->rays[i].len - map->rays[i + j + 1].len < 5) && (j >= 1 && j < 100))
		{
			dof = 0;
			while (dof < j)
			{
				map->rays[i + dof + 1].len = map->rays[i].len;
				dof++;
			}
		}
		j = 1;
	}
	i = -1;
	// print 3d map
	i = -1;
	int	color;
	while (++i < ray_num)
	{
		lineH = (BLK_WDT * 800) / map->rays[i].len + 0.01;
		lineO = 470 - (lineH / 3) + 0.01;
		init_mycoord(&coord1, (i * 1), lineO);
		init_mycoord(&coord2, (i * 1), lineH + lineO);
		if (map->rays[i].xmin == 0)
		{
			// if (map->rays[i].left == 0)
				color = 0x3D0AE5;
			// else
			// 	color = 0x565CFF;
		}
		else if (map->rays[i].xmin == 1)
		{
			// if (map->rays[i].up == 0)
				color = 0x0E18A5;
			// else
			// 	color = 0x3B3FAE;
		}
		if (map->rays[i].len != -1)
			connectdots(map->img, coord1, coord2, color);
	}
	free(map->rays);
	printf("------\n");
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
			while (++p < BLK_WDT - 1)
			{
				j = -1;
				while (++j < BLK_WDT - 1)
					put_p(map->img, x * BLK_WDT + p, y * BLK_WDT + j, color);
			}
			if (map->coord[y][x] == 'N' || map->coord[y][x] == 'S' || map->coord[y][x] == 'E' || map->coord[y][x] == 'W')
			{
				map->player->xmap = x;
				map->player->ymap = y;
				put_p(map->img, (x * BLK_WDT) + map->player->x, (y * BLK_WDT) + map->player->y, 0xFFFF00);
				put_p(map->img, (x * BLK_WDT) + map->player->x + 1, (y * BLK_WDT) + map->player->y, 0xFFFF00);
				put_p(map->img, (x * BLK_WDT) + map->player->x, (y * BLK_WDT) + map->player->y - 1, 0xFFFF00);
				put_p(map->img, (x * BLK_WDT) + map->player->x + 1, (y * BLK_WDT) + map->player->y - 1, 0xFFFF00);
				color = -1; //reuse this var to create dots for direction
				while (++color < 20)
					put_p(map->img, (x * BLK_WDT) + map->player->x + (map->player->dx * color / 4), (y * BLK_WDT) + map->player->y + (map->player->dy * color / 4), 0xFFFF00);
			}
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
		mlx_key_hook(map.win, deal_key, &map);
		createScreen(&map);
		mlx_loop(map.mlx);
	}
	else
		printf("input file name.");
	return (0);
}
