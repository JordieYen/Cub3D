/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cartesianplane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:13:14 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 17:11:08 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	countxlen(char *line)
{
	int	i;
	int	ispace;
	int	xlen;

	i = 0;
	xlen = 0;
	ispace = 0;
	while (line[i] != '\n')
	{
		if (line[i] != ' ' && ispace == 0)
		{
			ispace = 1;
			xlen++;
		}
		else
		{
			if (line[i] == ' ')
				ispace = 0;
		}
		i++;
	}
	free(line);
	return (xlen);
}

void	get_row_z(t_cartesian *chart, char *line, int xlen)
{
	char		**temp;
	int			i;
	static int	j;

	i = 0;
	temp = ft_split(line, ' ');
	free(line);
	i = 0;
	while (i < xlen)
	{
		chart->coords[j][i].z = ft_atoi(temp[i]);
		i++;
	}
	freearg(temp);
	j++;
}

void	get_z(t_cartesian *chart, char *file, int xlen, int ylen)
{
	int			fd;
	int			i;

	i = 0;
	fd = open(file, O_RDONLY);
	while (i < ylen)
	{
		get_row_z(chart, get_next_line(fd), xlen);
		i++;
	}
	close(fd);
}

void	get_x(t_cartesian *chart, int start, int space)
{
	int	i;
	int	j;
	int	temp;

	i = 0;
	while (i < chart->ylen)
	{
		j = 0;
		temp = start;
		while (j < chart->xlen)
		{
			chart->coords[i][j].x = temp;
			temp += space;
			j++;
		}
		i++;
	}
}

void	get_y(t_cartesian *chart, int start, int space)
{
	int	i;
	int	j;

	i = 0;
	while (i < chart->ylen)
	{
		j = 0;
		while (j < chart->xlen)
		{
			chart->coords[i][j].y = start;
			j++;
		}
		start += space;
		i++;
	}
}
