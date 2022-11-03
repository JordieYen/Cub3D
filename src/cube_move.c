/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:13:12 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/03 14:49:57 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#define DR 0.0174533

void	rotate_screen(t_map *map, int key)
{
	if (key == 2)
	{
		map->player->angle += DR * 3;
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	if (key == 0)
	{
		map->player->angle -= DR * 3;
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
}

void	update_posix(t_map *map, int attribute)
{
	map->player->x += (map->player->dx * attribute);
	map->player->y += (map->player->dy * attribute);
}

void	move_player(t_map *map, int key)
{
	if (key == 14)
		handledoors(map);
	if (key == 1)
	{
		if (map->coord[(int)(map->player->y - map->player->dy)]
			[(int)(map->player->x - map->player->dx)] != '1'
			&& map->coord[(int)(map->player->y - map->player->dy)]
			[(int)(map->player->x - map->player->dx)] != 'C')
			update_posix(map, -1);
	}
	if (key == 13)
	{
		if (map->coord[(int)(map->player->y + map->player->dy * 2)]
			[(int)(map->player->x + map->player->dx * 2)] != '1'
			&& map->coord[(int)(map->player->y + map->player->dy * 2)]
			[(int)(map->player->x + map->player->dx * 2)] != 'C')
			update_posix(map, 1);
	}
	if (key == 2 || key == 0)
		rotate_screen(map, key);
}

int	deal_key(int key, t_map *map)
{
	if (key == 13 || key == 1 || key == 14 || key == 2 || key == 0)
		move_player(map, key);
	if (key == 12)
		equipweapon(map);
	if (key == 15)
		swapweapon(map);
	if (key == 4)
		jumpscare(map);
	if (key == 3)
		map->attack = 8;
	if (key == 18)
		darken(map);
	if (key == 53)
	{
		free_map(map);
		system("leaks cub3D");
		exit(1);
	}
	return (0);
}

int	read_mouse(int x, int y, t_map *map)
{
	int	dir;

	y = 0;
	dir = 100 - x;
	mlx_mouse_move(map->win, 100, 100);
	if (dir < 0)
	{
		map->player->angle += DR * (dir * -1 / 5);
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	if (dir > 0)
	{
		map->player->angle -= DR * (dir / 5);
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	return (0);
}
