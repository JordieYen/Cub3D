/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   frees.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:13:26 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/16 17:10:34 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	freechart(t_cartesian *chart)
{
	int	i;

	i = 0;
	while (chart->coords[i])
	{
		free(chart->coords[i]);
		i++;
	}
	free(chart->coords);
}

void	freearg(char **arg)
{
	int	i;

	i = 0;
	while (arg[i])
	{
		free(arg[i]);
		i++;
	}
	free(arg);
}
