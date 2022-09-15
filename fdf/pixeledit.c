/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pixeledit.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:13:36 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 16:31:17 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_p(t_data *data, int x, int y, int color)
{
	char	*dst;

	if (y < 1080 && x < 1920)
	{
		if (y > 0 && x > 0)
		{
			dst = data->addr + (y * data->line_length + x
					* (data->bits_per_pixel / 8));
			*(unsigned int *)dst = color;
		}
	}
}

static int	i_s(int num1, int num2)
{
	if (num1 < num2)
		return (1);
	return (-1);
}

void	connectdots(t_data *img, t_coord coord0, t_coord coord1, int color)
{
	t_coord	d;
	t_coord	s;
	t_coord	e;

	init_coord(&d, abs(coord1.x - coord0.x), -abs(coord1.y - coord0.y), 0);
	init_coord(&s, i_s(coord0.x, coord1.x), i_s(coord0.y, coord1.y), 0);
	init_coord(&e, d.x + d.y, 0, 0);
	while (1)
	{
		put_p(img, coord0.x, coord0.y, color);
		if (coord0.x == coord1.x && coord0.y == coord1.y)
			break ;
		e.y = 2 * e.x;
		if (e.y >= d.y)
		{
			e.x += d.y;
			coord0.x += s.x;
		}
		if (e.y <= d.x)
		{
			e.x += d.x;
			coord0.y += s.y;
		}
	}
}

void	rotatedot(t_coord coord, t_coord center, t_coord *newchart)
{
	t_coord	temp;
	t_coord	rotated_point;

	init_coord(&temp, 0, 0, 0);
	temp.x = coord.x - center.x;
	temp.y = coord.y - center.y;
	init_coord(&rotated_point, 0, 0, 0);
	rotated_point.x = (cos(30 * (M_PI / 180)) * temp.x)
		- (sin(50 * (M_PI / 180)) * temp.y);
	rotated_point.y = (sin(30 * (M_PI / 180)) * temp.x)
		+ (cos(50 * (M_PI / 180)) * temp.y);
	rotated_point.x += center.x;
	rotated_point.y += center.y;
	newchart->x = rotated_point.x;
	newchart->y = rotated_point.y;
}

void	rotatechart(t_data *img, t_cartesian *chart, t_coord center)
{
	t_cartesian	rotated_chart;
	int			countx;
	int			county;

	county = 0;
	init_cartesian(&rotated_chart, chart->xlen, chart->ylen);
	while (county < (chart->ylen))
	{
		countx = 0;
		while (countx < (chart->xlen))
		{
			rotatedot(chart->coords[county][countx],
				center, &rotated_chart.coords[county][countx]);
			countx++;
		}
		county++;
	}
	copyz(chart, &rotated_chart);
	movetocenter(&rotated_chart, center);
	updatez(&rotated_chart);
	drawgrid(&rotated_chart, img, 0x0066B2FF);
	freechart(&rotated_chart);
}
