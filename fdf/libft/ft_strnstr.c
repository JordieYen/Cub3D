/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/28 15:42:07 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/12 00:40:09 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *hay, const char *needle, unsigned int n)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (*needle == 0)
		return (hay);
	while (hay[i] != '\0' && i < n)
	{
		j = 0;
		while ((hay[i + j] == needle[j]) && (i + j) < n)
		{
			if (needle[j + 1] == '\0')
				return (hay + i);
			j++;
		}
		i++;
	}
	return (0);
}
