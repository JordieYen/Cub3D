/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 19:51:23 by jking-ye          #+#    #+#             */
/*   Updated: 2021/11/18 14:18:29 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(const void *str)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (s[i] != '\0')
		i++;
	return (i);
}

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

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char			*ptr;
	unsigned int	i;
	unsigned int	lens;

	i = 0;
	if (!s)
		return (0);
	lens = (unsigned int)ft_strlen(s);
	if (start + len > lens)
		len = lens - start;
	if (start > lens)
		len = 0;
	ptr = (char *)malloc(sizeof(char) * (len + 1));
	if (!ptr)
		return (0);
	while (i < len && s[start + i] != '\0')
	{
		ptr[i] = s[start + i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}

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
