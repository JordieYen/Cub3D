/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minecraft.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 19:58:11 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/03 14:42:18 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdio.h>
#include "../includes/mlx.h"
#include <stdlib.h>
#include <math.h>
#include <limits.h>

t_wall	changeblockframe(t_map *map)
{
	t_wall		frame;
	static int	i;

	frame = map->blockhand[0];
	frame.wall_width -= 200;
	if (map->attack > 0 && map->attack < 9)
	{
		if (map->attack == 8)
		{
			i = 0;
			map->attack--;
		}
		if (i < 8)
			i++;
		else
			map->attack = 0;
		frame = map->blockhand[i];
	}
	return (frame);
}

void	free_blockhand(t_map *map)
{
	mlx_destroy_image(map->mlx, map->blockhand[0].wall);
	mlx_destroy_image(map->mlx, map->blockhand[1].wall);
	mlx_destroy_image(map->mlx, map->blockhand[2].wall);
	mlx_destroy_image(map->mlx, map->blockhand[3].wall);
	mlx_destroy_image(map->mlx, map->blockhand[4].wall);
	mlx_destroy_image(map->mlx, map->blockhand[5].wall);
	mlx_destroy_image(map->mlx, map->blockhand[6].wall);
	mlx_destroy_image(map->mlx, map->blockhand[7].wall);
	mlx_destroy_image(map->mlx, map->blockhand[8].wall);
	free(map->blockhand);
}

void	get_minecraft(t_map *map)
{
	map->blockhand = malloc(sizeof(t_wall) * 9);
	map->blockhand[0].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/01.xpm",
			&map->blockhand[0].wall_width, &map->blockhand[0].wall_height);
	map->blockhand[1].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/02.xpm",
			&map->blockhand[1].wall_width, &map->blockhand[1].wall_height);
	map->blockhand[2].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/03.xpm",
			&map->blockhand[2].wall_width, &map->blockhand[2].wall_height);
	map->blockhand[3].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/04.xpm",
			&map->blockhand[3].wall_width, &map->blockhand[3].wall_height);
	map->blockhand[4].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/05.xpm",
			&map->blockhand[4].wall_width, &map->blockhand[4].wall_height);
	map->blockhand[5].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/06.xpm",
			&map->blockhand[5].wall_width, &map->blockhand[5].wall_height);
	map->blockhand[6].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/07.xpm",
			&map->blockhand[6].wall_width, &map->blockhand[6].wall_height);
	map->blockhand[7].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/01.xpm",
			&map->blockhand[7].wall_width, &map->blockhand[7].wall_height);
	map->blockhand[8].wall = mlx_xpm_file_to_image(&map->mlx, "./frames/01.xpm",
			&map->blockhand[8].wall_width, &map->blockhand[8].wall_height);
}
