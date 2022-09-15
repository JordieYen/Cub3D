/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chart_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:22:59 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 16:23:08 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	plot_chart(t_cartesian *chart, t_data *img)
{
	int	countx;
	int	county;

	county = 0;
	while (county < chart->ylen)
	{
		countx = 0;
		while (countx < chart->xlen)
		{
			put_p(img, chart->coords[county][countx].x,
				chart->coords[county][countx].y, 0x00FFFFFF);
			countx++;
		}
		county++;
	}
}

void	updatez(t_cartesian *chart)
{
	int	countx;
	int	county;
	int	space;

	county = 0;
	space = 1920 / (chart->xlen * 2);
	while (county < (chart->ylen))
	{
		countx = 0;
		while (countx < (chart->xlen))
		{
			chart->coords[county][countx].y
				-= (chart->coords[county][countx].z * 4);
			countx++;
		}
		county++;
	}
}

void	movetocenter(t_cartesian *chart, t_coord center)
{
	int	diffx;
	int	diffy;
	int	countx;
	int	county;

	diffx = (1920 / 2) - center.x;
	diffy = (1080 / 2) - center.y;
	county = 0;
	while (county < (chart->ylen))
	{
		countx = 0;
		while (countx < (chart->xlen))
		{
			chart->coords[county][countx].x += diffx;
			chart->coords[county][countx].y += diffy;
			countx++;
		}
		county++;
	}
}
