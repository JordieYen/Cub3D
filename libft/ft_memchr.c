/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/19 14:35:37 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/13 11:38:42 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *str, int c, size_t n)
{
	unsigned long	i;
	char			*s;
	char			ch;

	i = 0;
	s = (char *)str;
	ch = c;
	while (i < n)
	{
		if (s[i] == ch)
			return (&s[i]);
		i++;
	}
	return (0);
}
