/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:13:12 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 20:13:51 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/mlx.h"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

void	rotate_screen(t_map *map, int key)
{
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

void	move_player(t_map *map, int key)
{
	if (key == E)
		handledoors(map);
	if (key == S)
	{
		if (map->coord[(int)(map->player->y - map->player->dy)]
			[(int)(map->player->x - map->player->dx)] != '1'
			&& map->coord[(int)(map->player->y - map->player->dy)]
			[(int)(map->player->x - map->player->dx)] != 'C')
		{
			map->player->x -= map->player->dx;
			map->player->y -= map->player->dy;
		}
	}
	if (key == W)
	{
		if (map->coord[(int)(map->player->y + map->player->dy * 2)]
			[(int)(map->player->x + map->player->dx * 2)] != '1'
			&& map->coord[(int)(map->player->y + map->player->dy * 2)]
			[(int)(map->player->x + map->player->dx * 2)] != 'C')
		{
			map->player->x += map->player->dx;
			map->player->y += map->player->dy;
		}
	}
	if (key == D || key == A)
		rotate_screen(map, key);
}

int	deal_key(int key, t_map *map)
{
	if (key == W || key == S || key == E || key == D || key == A)
		move_player(map, key);
	if (key == Q)
		equipweapon(map);
	if (key == R)
		swapweapon(map);
	if (key == 53)
	{
		free_map(map);
		system("leaks cub3d");
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
		map->player->angle += DR * (dir * -1 / 2);
		if (map->player->angle > 2 * PI)
			map->player->angle = map->player->angle - 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	if (dir > 0)
	{
		map->player->angle -= DR * (dir / 2);
		if (map->player->angle < 0)
			map->player->angle = map->player->angle + 2 * PI;
		map->player->dx = cos(map->player->angle) / 10;
		map->player->dy = sin(map->player->angle) / 10;
	}
	return (0);
}
