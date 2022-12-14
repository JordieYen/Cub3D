/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/24 16:53:53 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:36 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const char *s1, const char *s2, size_t n)
{
	unsigned char	c1;
	unsigned char	c2;
	unsigned long	i;

	i = 0;
	while (i < n)
	{
		c1 = s1[i];
		c2 = s2[i++];
		if ((c1 - c2) != 0)
			return (c1 - c2);
	}
	return (0);
}
