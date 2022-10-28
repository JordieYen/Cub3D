/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/29 12:05:08 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:07:13 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

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
