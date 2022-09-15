/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 13:38:57 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/13 11:39:06 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *s1, const void *s2, char c, size_t n)
{
	unsigned long	i;
	char			*one;
	char			*two;

	i = 0;
	one = (char *)s1;
	two = (char *)s2;
	while (i < n)
	{
		one[i] = two[i];
		if (two[i] == c)
			return (&(s1[i + 1]));
		i++;
	}
	return (0);
}
