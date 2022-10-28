/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_doors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:36:26 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/28 20:10:28 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <math.h>

int	check_if_valid(t_map *map, int offset, char door, char axis)
{
	if (axis == 'x')
	{
		if (map->player->x + offset < map->xlen
			&& map->player->y + offset < map->ylen)
		{
			if (map->coord[(int)(map->player->y)]
				[(int)(map->player->x + offset)] == door)
				return (1);
		}
	}
	if (axis == 'y')
	{
		if (map->player->x + offset < map->xlen
			&& map->player->y + offset < map->ylen)
		{
			if (map->coord[(int)(map->player->y + offset)]
				[(int)(map->player->x)] == door)
				return (1);
		}
	}
	return (0);
}

void	opendoor(t_map *map)
{
	if (check_if_valid(map, -1, 'C', 'y'))
		map->coord[(int)(map->player->y - 1)][(int)(map->player->x)] = 'O';
	else if (check_if_valid(map, -2, 'C', 'y'))
		map->coord[(int)(map->player->y - 2)][(int)(map->player->x)] = 'O';
	if (check_if_valid(map, 1, 'C', 'y'))
		map->coord[(int)(map->player->y + 1)][(int)(map->player->x)] = 'O';
	else if (check_if_valid(map, 2, 'C', 'y'))
		map->coord[(int)(map->player->y + 2)][(int)(map->player->x)] = 'O';
	if (check_if_valid(map, -1, 'C', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x - 1)] = 'O';
	else if (check_if_valid(map, -2, 'C', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x - 2)] = 'O';
	if (check_if_valid(map, 1, 'C', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x + 1)] = 'O';
	else if (check_if_valid(map, 2, 'C', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x + 2)] = 'O';
}

void	closedoor(t_map *map)
{
	if (check_if_valid(map, -1, 'O', 'y'))
		map->coord[(int)(map->player->y - 1)][(int)(map->player->x)] = 'C';
	else if (check_if_valid(map, -2, 'O', 'y'))
		map->coord[(int)(map->player->y - 2)][(int)(map->player->x)] = 'C';
	if (check_if_valid(map, 1, 'O', 'y'))
		map->coord[(int)(map->player->y + 1)][(int)(map->player->x)] = 'C';
	else if (check_if_valid(map, 2, 'O', 'y'))
		map->coord[(int)(map->player->y + 2)][(int)(map->player->x)] = 'C';
	if (check_if_valid(map, -1, 'O', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x - 1)] = 'C';
	else if (check_if_valid(map, -2, 'O', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x - 2)] = 'C';
	if (check_if_valid(map, 1, 'O', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x + 1)] = 'C';
	else if (check_if_valid(map, 2, 'O', 'x'))
		map->coord[(int)(map->player->y)][(int)(map->player->x + 2)] = 'C';
}

void	handledoors(t_map *map)
{
	static int	isclosed;

	if (map->player->x - floor(map->player->x) >= 0.00001
		&& map->player->y - floor(map->player->y) >= 0.00001)
	{
		if (isclosed == 0)
		{
			opendoor(map);
			isclosed = 1;
		}
		else
		{
			closedoor(map);
			isclosed = 0;
		}
	}
}
