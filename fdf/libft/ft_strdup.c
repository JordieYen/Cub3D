/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/27 16:46:56 by jking-ye          #+#    #+#             */
/*   Updated: 2021/07/12 01:17:08 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s)
{
	char			*ptr;
	unsigned long	i;
	unsigned long	len;

	i = 0;
	len = 0;
	while (s[len] != '\0')
		len++;
	ptr = malloc(len + 1);
	if (ptr == 0)
		return (0);
	while (i < len)
	{
		ptr[i] = s[i];
		i++;
	}
	ptr[i] = '\0';
	return (ptr);
}
