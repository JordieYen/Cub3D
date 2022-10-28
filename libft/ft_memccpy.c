/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 13:38:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:30 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
