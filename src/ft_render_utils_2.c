/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_render_utils_2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 13:03:21 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/02 20:22:02 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdio.h>
#include <math.h>
#define BLK_WDT 1
#define BLK_WDT_PXL 32
#define DR 0.0174533

void	opendooranimation(t_ray *ray, char c)
{
	static float	temp;

	if (c == 'C')
	{
		if (temp - 0.3 > -0.7)
			temp -= 0.3;
	}
	if (c == 'O')
	{
		if (temp + 0.3 < 1.3)
			temp += 0.3;
	}
	ray->doorwidth = temp;
}

int	getdoorlen(t_ray *ray, float distance, char c)
{
	float	ca;
	float	dist_t;

	if (c == '1')
		return (true);
	if (ray->firstdoor == 1)
		return (false);
	ca = ray->playerangle - ray->angle;
	dist_t = distance * BLK_WDT_PXL;
	if (ca < 0)
		ca += 2 * PI;
	if (ca > 2 * PI)
		ca -= 2 * PI;
	if (dist_t != -1)
		dist_t = dist_t * cos(ca);
	ray->doorlen = dist_t;
	ray->doorxmin = ray->xmin;
	ray->isdoor = 'y';
	ray->doorx = (ray->start.x + ray->dir.x * distance);
	ray->doory = (ray->start.y + ray->dir.y * distance);
	ray->firstdoor = 1;
	return (false);
}

float	rotate_angle(float angle)
{
	angle += DR / 16;
	if (angle < 0)
		angle += 2 * PI;
	if (angle > 2 * PI)
		angle -= 2 * PI;
	return (angle);
}
