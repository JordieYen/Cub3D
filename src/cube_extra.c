/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_extra.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 14:51:48 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/01 16:09:24 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include "../includes/libft.h"
#include <unistd.h>
#include "../includes/get_next_line.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>
#define PI 3.14159265359

void	compare_walls(char *dir, t_map *map, char **args)
{
	if (access(dir, F_OK) == 0)
	{
		if (!ft_strncmp(args[0], "NO", 1))
			check_wall_dir(&map->tex->wall_no_dir, dir);
		if (!ft_strncmp(args[0], "SO", 1))
			check_wall_dir(&map->tex->wall_so_dir, dir);
		if (!ft_strncmp(args[0], "WE", 1))
			check_wall_dir(&map->tex->wall_we_dir, dir);
		if (!ft_strncmp(args[0], "EA", 1))
			check_wall_dir(&map->tex->wall_ea_dir, dir);
		if (!ft_strncmp(args[0], "DO", 1))
			check_wall_dir(&map->tex->wall_do_dir, dir);
	}
	else
		perror("ACCESS ERROR\n");
}

void	assign_floor_ceiling_color(int rgb, t_map *map, char *line, int tc)
{
	if (!ft_strncmp(line, "F", 1) && rgb == 3)
	{
		if (map->f_color == UINT_MAX)
			map->f_color = tc;
		else
			error_exit("Error: double color key\n");
	}
	if (!ft_strncmp(line, "C", 1) && rgb == 3)
	{
		if (map->c_color == UINT_MAX)
			map->c_color = tc;
		else
			error_exit("Error: double color key\n");
	}
}

void	configure_map(t_map *map, int fd, char *line)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (line != NULL && ++y)
	{
		if (ft_strlen(line) > x)
			x = ft_strlen(line);
		free(line);
		line = get_next_line(fd);
	}
	if (line)
		free(line);
	map->xlen = x - 1;
	map->ylen = y;
	if (y > 0)
		map->coord = malloc((y + 1) * sizeof(char *));
	y = 0;
	while (y < map->ylen)
	{
		map->coord[y] = malloc((x + 2) * sizeof(char));
		y++;
	}
	map->player = malloc(sizeof(t_player));
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

void	set_start_direction(t_map *map)
{
	if (map->player->start_char == 'N')
		map->player->angle = 3 * PI / 2;
	else if (map->player->start_char == 'S')
		map->player->angle = PI / 2;
	else if (map->player->start_char == 'E')
		map->player->angle = PI * 2;
	else if (map->player->start_char == 'W')
		map->player->angle = PI;
	map->player->dx = cos(map->player->angle) / 10;
	map->player->dy = sin(map->player->angle) / 10;
}
