/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/02 18:32:57 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:58 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
