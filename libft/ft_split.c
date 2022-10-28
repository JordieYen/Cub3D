/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/07/14 14:18:33 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:55 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static	int	wordcount(const char *s, char c)
{
	int	i;
	int	count;
	int	isword;

	i = 0;
	count = 0;
	isword = 0;
	while (s[i] != '\0')
	{
		if (isword == 0 && s[i] != c)
		{
			count++;
			isword = 1;
		}
		else if (s[i] == c)
			isword = 0;
		i++;
	}
	return (count);
}

char	**ft_split(const char *s, char c)
{
	int		i;
	int		j;
	int		k;
	char	**ptr;

	i = 0;
	k = 0;
	if (!s)
		return (0);
	ptr = ft_calloc((wordcount(s, c) + 1), 8);
	if (!ptr)
		return (0);
	while (s[i] != '\0')
	{
		if (s[i] != c)
		{
			j = 0;
			while (s[i + j + 1] != c && s[i + j + 1] != 0)
				j++;
			ptr[k++] = ft_substr(s, i, j + 1);
			i = i + j;
		}
		i++;
	}
	return (ptr);
}
