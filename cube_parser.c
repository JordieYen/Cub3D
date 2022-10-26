/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:32:17 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/25 16:45:37 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include "libft/libft.h"
#include <unistd.h>
#include "libgnl/get_next_line.h"
#include <math.h>
#include <stdio.h>

static int	check_space(t_map *map, int x, int y)
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

void	read_cub(t_map *map, int fd)
{
	int		x;
	int		y;
    int     n;
	char	*line;

	line = get_next_line(fd);
    n = 1;
	while (line != NULL)
	{
        if (!ft_strncmp(line, "NO", 2) || !ft_strncmp(line, "SO", 2)
            || !ft_strncmp(line, "WE", 2) || !ft_strncmp(line, "EA", 2)
			|| !ft_strncmp(line, "DO", 2))
        	init_texture(map, line);
        if (!ft_strncmp(line, "F", 1) || !ft_strncmp(line, "C", 1))
            init_color(map, line);
        free(line);
		line = get_next_line(fd);
        if (textures_color_filled(map, 3))
            break;
        n++;
	}
	if (line == NULL)
		return ;
    while (*line == '\n' && ++n)
    {
        free(line);
		line = get_next_line(fd);
    }
    map->map_start_n = n;
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

    while (map->map_start_n--)
        free(get_next_line(fd));
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

int check_map(t_map *map)
{
    int	j;
	int	i;

    i = 0;
    while (map->coord[i] != NULL)
	{
		j = 0;
		while (map->coord[i][j] != '\0')
		{
			if (map->coord[i][j] != '0' && map->coord[i][j] != '1'
				&& map->coord[i][j] != ' ' && map->coord[i][j] != 'N'
				&& map->coord[i][j] != 'S' && map->coord[i][j] != 'E'
				&& map->coord[i][j] != 'W' && map->coord[i][j] != 'C')
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

int	check_cub(t_map *map, char *config_map)
{
    int fd;

	map->tex = malloc(sizeof(t_tex));
    init_zero(map);
    fd = open(config_map, O_RDONLY);
    read_cub(map, fd);
	if (!textures_color_filled(map, 3))
    {
        ft_putstr_fd("Error: parsing textures and/or color\n", 2);
        return (0);
    }
	close(fd);
    fd = open(config_map, O_RDONLY);
    fill_map(map, fd);
    if (!check_map(map))
        return (0);
    return (1);
}
