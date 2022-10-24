/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_shadows.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bunyodshams <bunyodshams@student.42.fr>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/23 01:42:49 by bunyodshams       #+#    #+#             */
/*   Updated: 2022/10/23 01:42:50 by bunyodshams      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube3d.h"
#include "libft/libft.h"
#include <stdio.h>

int	darken_int(int rgb, float percentage)
{
	int		value;

	value = (int)rgb - (rgb * percentage);
	if (value < 0)
		value = 0;
	if (value > 255)
		value = 255;
	return (value);
}

int	darken_rgb(int rgb, float len)
{
	unsigned int	red;
	unsigned int	green;
	unsigned int	blue;
	unsigned int	urgb;

	urgb = rgb;
	red = (urgb >> 16);
	green = (((urgb >> 8) << 24) >> 24);
	blue = ((urgb << 24) >> 24);
	red = darken_int(red, 0.003 * len);
	green = darken_int(green, 0.003 * len);
	blue = darken_int(blue, 0.003 * len);
	red = (red << 8) + green;
	red = (red << 8) + blue;
	return (red);
}
