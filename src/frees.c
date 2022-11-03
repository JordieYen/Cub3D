/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 20:03:36 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/02 20:22:18 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdlib.h>
#include <stdio.h>
#include "../includes/mlx.h"

void	free_coord(t_map *map)
{
	int	y;

	y = 0;
	while (y < map->ylen + 1)
	{
		free(map->coord[y]);
		y++;
	}
	free(map->coord);
}

void	free_texture(t_map *map)
{
	free(map->tex->wall_no_dir);
	free(map->tex->wall_so_dir);
	free(map->tex->wall_ea_dir);
	free(map->tex->wall_we_dir);
	free(map->tex->wall_do_dir);
	free(map->tex);
}

void	free_hand(t_map *map)
{
	free_blockhand(map);
	mlx_destroy_image(map->mlx, map->hand[0].wall);
	mlx_destroy_image(map->mlx, map->hand[1].wall);
	mlx_destroy_image(map->mlx, map->hand[2].wall);
	mlx_destroy_image(map->mlx, map->hand[3].wall);
	mlx_destroy_image(map->mlx, map->hand[4].wall);
	mlx_destroy_image(map->mlx, map->hand[5].wall);
	mlx_destroy_image(map->mlx, map->hand[6].wall);
	mlx_destroy_image(map->mlx, map->hand[7].wall);
	mlx_destroy_image(map->mlx, map->hand[8].wall);
	mlx_destroy_image(map->mlx, map->hand[9].wall);
	free(map->hand);
}

void	free_walls(t_map *map)
{
	mlx_destroy_image(map->mlx, map->knife.wall);
	mlx_destroy_image(map->mlx, map->jump.wall);
	mlx_destroy_image(map->mlx, map->wall_n.wall);
	mlx_destroy_image(map->mlx, map->wall_s.wall);
	mlx_destroy_image(map->mlx, map->wall_e.wall);
	mlx_destroy_image(map->mlx, map->wall_w.wall);
	mlx_destroy_image(map->mlx, map->door.wall);
}

void	free_map(t_map *map)
{
	free_coord(map);
	free(map->player);
	free_texture(map);
	free_hand(map);
	free_walls(map);
	mlx_destroy_window(map->mlx, map->win);
	free(map);
}
