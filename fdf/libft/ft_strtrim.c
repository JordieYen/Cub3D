/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/30 13:52:38 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/19 19:29:59 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

char	*ft_strtrim(char const *s, char const *set)
{
	char	*ptr;
	int		f;
	int		e;

	f = 0;
	e = ft_strlen(s);
	ptr = 0;
	if (s != 0 && set != 0)
	{
		while (s[f] && ft_strchr(set, s[f]))
			f++;
		while (s[e - 1] && ft_strchr(set, s[e - 1]) && e > f)
			e--;
		ptr = malloc(e - f + 1);
		if (ptr)
			ft_strlcpy(ptr, &s[f], e - f + 1);
	}
	return (ptr);
}
