/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/28 19:21:31 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/19 19:44:08 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const void *s1, const void *s2)
{
	char	*ptr;
	int		i;
	char	*one;
	char	*two;

	i = 0;
	one = (char *)s1;
	two = (char *)s2;
	ptr = malloc(ft_strlen(one) + ft_strlen(two) + 1);
	if (!ptr)
		return (0);
	while (one[i] != '\0')
	{
		ptr[i] = one[i];
		i++;
	}
	i = 0;
	while (two[i] != '\0')
	{
		ptr[ft_strlen(one) + i] = two[i];
		i++;
	}
	ptr[ft_strlen(one) + i] = '\0';
	return (ptr);
}
