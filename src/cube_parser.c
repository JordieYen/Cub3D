/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 11:32:17 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/11/01 15:30:03 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include "../includes/libft.h"
#include <unistd.h>
#include "../includes/get_next_line.h"
#include <math.h>
#include <stdio.h>

int	read_cub(t_map *map, int fd)
{
	int		n;
	char	*line;

	line = get_next_line(fd);
	n = 1;
	while (line != NULL)
	{
		if (!init_texture_color(map, line))
			return (0);
		free(line);
		line = get_next_line(fd);
		if (textures_color_filled(map, 3))
			break ;
		n++;
	}
	if (line == NULL)
		return (0);
	while (*line == '\n' && ++n)
	{
		free(line);
		line = get_next_line(fd);
	}
	map->map_start_n = n;
	configure_map(map, fd, line);
	return (1);
}

void	fill_map(t_map *map, int fd)
{
	int		i;
	int		j;
	char	*line;

	while (map->map_start_n--)
		free(get_next_line(fd));
	i = -1;
	while (++i < map->ylen)
	{
		j = -1;
		line = get_next_line(fd);
		while (j++ < map->xlen + 2)
		{
			if (j < ft_strlen(line) - 1)
				map->coord[i][j] = line[j];
			else
				map->coord[i][j] = ' ';
			if (j == map->xlen + 1)
				map->coord[i][j] = '\0';
		}
		free(line);
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

int	check_map(t_map *m)
{
	int	j;
	int	i;

	i = -1;
	while (m->coord[++i] != NULL)
	{
		j = -1;
		while (m->coord[i][++j] != '\0')
		{
			if (m->coord[i][j] != '0' && m->coord[i][j] != '1'
				&& m->coord[i][j] != ' ' && m->coord[i][j] != 'N'
				&& m->coord[i][j] != 'S' && m->coord[i][j] != 'E'
				&& m->coord[i][j] != 'W' && m->coord[i][j] != 'C')
				return (0);
			else if (m->coord[i][j] != 'N'
				&& m->coord[i][j] != 'S' && m->coord[i][j] != 'E'
				&& m->coord[i][j] != 'W')
				m->direction = m->coord[i][j];
		}
	}
	if (!check_walls(m))
		return (0);
	return (1);
}

int	check_cub(t_map *map, char *cm)
{
	int	fd;

	if (ft_strlen(cm) < 4 || (ft_strncmp(&cm[ft_strlen(cm) - 4], ".cub", 4)))
		error_exit("Error: file is not .cub\n");
	map->tex = malloc(sizeof(t_tex));
	init_zero(map);
	fd = open(cm, O_RDONLY);
	if (!read_cub(map, fd) || !textures_color_filled(map, 3) || fd == -1)
	{
		if (fd == -1)
			error_exit("Error: can't read config file\n");
		else
			error_exit("Error: parsing textures and/or color\n");
	}
	close(fd);
	fd = open(cm, O_RDONLY);
	fill_map(map, fd);
	set_player_posix(map);
	set_start_direction(map);
	close(fd);
	if (!check_map(map))
		return (0);
	return (1);
}
