/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:32:57 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/21 15:12:20 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *str, int chr)
{
	int		i;
	char	c;
	char	*s;

	i = 0;
	c = chr;
	s = (char *)str;
	if (chr == '\0')
		return (&s[ft_strlen(s)]);
	while (s[i] != '\0')
	{
		if (chr == '\0')
		{
			if (s[i + 1] == '\0')
				return (&s[i + 1]);
		}
		if (s[i] == c)
			return (&s[i]);
		i++;
	}
	return (0);
}
