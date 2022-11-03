/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frames.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:35:25 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/02 20:22:49 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include "../includes/libft.h"
#include "../includes/get_next_line.h"
#include <stdio.h>
#include <math.h>
#include "../includes/mlx.h"
#include <float.h>
#include <stdlib.h>
#include <sys/time.h>

t_wall	changeframe(t_map *map)
{
	static int	i;
	static int	direction;
	t_wall		frame;

	frame = map->hand[9];
	if (i >= 0 && i <= 9)
		frame = map->hand[i];
	if (direction == 0 && map->equipweapon == 1)
	{
		if (i < 9)
			i++;
		else
			direction = 1;
	}
	else if (direction == 1 && map->equipweapon == 2)
	{
		if (i > 0)
			i--;
		else
			direction = 0;
	}
	return (frame);
}

void	rotate_i(int *i, int *direction)
{
	if (*direction == 0)
	{
		if (*i < 20)
			*i += 1;
		else
			*direction = 1;
	}
	else
	{
		if (*i > 0)
			*i -= 1;
		else
			*direction = 0;
	}
}

void	animatehand(t_map *map)
{
	static int	i;
	static int	direction;
	t_wall		frame;

	frame = changeframe(map);
	if (map->swapweapon == 3)
		frame = changeblockframe(map);
	if (map->swapweapon == 1 || map->swapweapon == 3)
		mlx_put_image_to_window(map->mlx, map->win, frame.wall,
			1440 - frame.wall_width, 810 - frame.wall_height + (i * 2));
	else
		mlx_put_image_to_window(map->mlx, map->win, map->knife.wall, 1440
			- map->knife.wall_width, 810 - map->knife.wall_height + (i * 2));
	if (map->jumps == 1)
		mlx_put_image_to_window(map->mlx, map->win, map->jump.wall, 0, 0);
	rotate_i(&i, &direction);
	map->offset = i;
}

void	put_framerate(t_map *map)
{
	struct timeval	tv;
	int				color;
	char			*fps_str;
	char			*fps_num;

	gettimeofday(&tv, NULL);
	map->fps = ((tv.tv_sec * 1000) + (tv.tv_usec / 1000)) - map->last_frame;
	map->last_frame = (tv.tv_sec * 1000) + (tv.tv_usec / 1000);
	color = 0xFFFFFF;
	if (1000 / map->fps >= 20)
		color = 0x00FF00;
	if (1000 / map->fps < 20)
		color = 0xFFFF00;
	if (1000 / map->fps < 10)
		color = 0xFF0000;
	fps_num = ft_itoa((float) 1000 / map->fps);
	fps_str = ft_strjoin("fps :", fps_num);
	mlx_string_put(map->mlx, map->win, 0, 10, color, fps_str);
	free(fps_num);
	free(fps_str);
}

int	render_screen(void *varg)
{
	t_map			*map;

	map = (t_map *) varg;
	mlx_clear_window(map->mlx, map->win);
	create_screen(map);
	animatehand(map);
	put_framerate(map);
	return (0);
}
