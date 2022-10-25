/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:40:07 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/25 16:09:07 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <limits.h>
#include <stdio.h>

void    init_zero(t_map *map)
{
	map->tex->wall_no_dir = NULL;
	map->tex->wall_so_dir = NULL;
	map->tex->wall_we_dir = NULL;
	map->tex->wall_ea_dir = NULL;
	map->tex->wall_do_dir = NULL;
	map->f_color = UINT_MAX;
	map->c_color = UINT_MAX;
}

int     textures_color_filled(t_map *map, int flag)
{
	//flag 1 only tex
	// 2 only color
	// 3 both
	if ((flag == 1 || flag == 3)
		&& (map->tex->wall_no_dir == NULL
		|| map->tex->wall_so_dir == NULL
		|| map->tex->wall_we_dir == NULL
		|| map->tex->wall_ea_dir == NULL
		|| map->tex->wall_do_dir == NULL))
	{
		if (flag != 3)
			return (0);
	}
	if ((flag == 3 || flag == 2)
		&& (map->f_color == UINT_MAX
		|| map->c_color == UINT_MAX))
		return (0);
	return (1);
}

void    init_color(t_map *map, char *line)
{
	unsigned int    color;
	char			*line_ref;
	int				rgb_num;

	line_ref = line;
	color = 0;
	rgb_num = 0;
	while (*line_ref)
	{
		if (*line_ref >= '0' && *line_ref <= '9')
		{
			rgb_num++;
			while (*line_ref && *line_ref >= '0' && *line_ref <= '9')
			{
				color = (color * 10) + (*line_ref - 48);
				line_ref++;
			}
			color = color << 8;
		}
		line_ref++;
	}
	if (!ft_strncmp(line, "F", 1) && rgb_num == 3)
		map->f_color = color;
	if (!ft_strncmp(line, "C", 1) && rgb_num == 3)
		map->c_color = color;
}

void    init_texture(t_map *map, char *line)
{
	char	**args;
	char	*dir;
	int		i;

	args = ft_split(line, ' ');
	i = -1;
	while (args[++i] != NULL);
	if (i != 2)
		return;
	dir = ft_strtrim(args[1], "\n");
	if (access(dir, F_OK) == 0)
	{
		if (!ft_strncmp(args[0], "NO", 1))
			map->tex->wall_no_dir = dir;
		if (!ft_strncmp(args[0], "SO", 1))
			map->tex->wall_so_dir = dir;
		if (!ft_strncmp(args[0], "WE", 1))
			map->tex->wall_we_dir = dir;
		if (!ft_strncmp(args[0], "EA", 1))
			map->tex->wall_ea_dir = dir;
		if (!ft_strncmp(args[0], "DO", 1))
			map->tex->wall_do_dir = dir;
	}
	else
		perror("ACCESS ERROR\n");
}