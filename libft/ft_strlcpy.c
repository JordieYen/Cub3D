/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/31 16:18:06 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:07:11 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

unsigned long	ft_strlcpy(void *dest, const void *src, unsigned int l)
{
	unsigned long	i;
	char			*d;
	char			*s;

	i = 0;
	d = (char *)dest;
	s = (char *)src;
	if (!src)
		return (0);
	if (l == 0)
	{
		while (s[i] != '\0')
			i++;
		return (i);
	}
	while (i < (l - 1) && s[i] != '\0')
	{
		d[i] = s[i];
		i++;
	}
	if (i < l)
		d[i] = '\0';
	while (s[i] != '\0')
		i++;
	return (i);
}
