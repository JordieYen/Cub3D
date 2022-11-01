/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_manipulation.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:16:16 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/01 16:23:37 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdio.h>

void	equipweapon(t_map *map)
{
	static int	i;

	if (i == 0)
	{
		map->equipweapon = 1;
		i = 1;
	}
	else if (i == 1)
	{
		map->equipweapon = 2;
		i = 0;
	}
}

void	swapweapon(t_map *map)
{
	static int	j;

	if (j == 0)
	{
		map->swapweapon = 1;
		j = 1;
	}
	else if (j == 1)
	{
		map->swapweapon = 2;
		j = 0;
	}
}

void	jumpscare(t_map *map)
{
	static int	j;

	if (j == 0)
	{
		map->jumps = 1;
		j = 1;
	}
	else if (j == 1)
	{
		map->jumps = 0;
		j = 0;
	}
}

void	darken(t_map *map)
{
	static int	j;

	if (j == 0)
	{
		map->darken = 1;
		j = 1;
	}
	else if (j == 1)
	{
		map->darken = 0;
		j = 0;
	}
}
