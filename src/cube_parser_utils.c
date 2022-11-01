/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_parser_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 12:40:07 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/11/01 16:09:45 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdlib.h>
#include <unistd.h>
#include "../includes/libft.h"
#include <limits.h>
#include <stdio.h>

int	free_pp(char **str)
{
	unsigned int	i;

	i = 0;
	while (str[i] && *str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (1);
}

void	init_zero(t_map *map)
{
	map->tex->wall_no_dir = NULL;
	map->tex->wall_so_dir = NULL;
	map->tex->wall_we_dir = NULL;
	map->tex->wall_ea_dir = NULL;
	map->tex->wall_do_dir = NULL;
	map->f_color = UINT_MAX;
	map->c_color = UINT_MAX;
}

int	textures_color_filled(t_map *map, int flag)
{
	if ((flag == 3)
		&& (map->tex->wall_no_dir == NULL
			|| map->tex->wall_so_dir == NULL
			|| map->tex->wall_we_dir == NULL
			|| map->tex->wall_ea_dir == NULL
			|| map->tex->wall_do_dir == NULL
			|| map->f_color == UINT_MAX
			|| map->c_color == UINT_MAX))
		return (0);
	return (1);
}

void	init_color(t_map *map, char *line)
{
	unsigned int	color;
	unsigned int	total_color;
	char			*line_ref;
	int				rgb_num;

	line_ref = line;
	rgb_num = 0;
	total_color = 0;
	while (*line_ref)
	{
		color = 0;
		if (*line_ref >= '0' && *line_ref <= '9')
		{
			rgb_num++;
			while (*line_ref && *line_ref >= '0' && *line_ref <= '9')
			{
				color = (color * 10) + (*line_ref - 48);
				line_ref++;
			}
		}
		total_color = (total_color << 8) + color;
		line_ref++;
	}
	assign_floor_ceiling_color(rgb_num, map, line, total_color);
}

void	init_texture(t_map *map, char *line)
{
	char	**args;
	char	*dir;
	int		i;

	args = ft_split(line, ' ');
	i = -1;
	while (args[++i] != NULL)
		;
	if (i != 2 && free_pp(args))
		return ;
	dir = ft_strtrim(args[1], "\n");
	compare_walls(dir, map, args);
	free(dir);
	free_pp(args);
}
