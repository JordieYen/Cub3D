/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 15:02:43 by jking-ye          #+#    #+#             */
/*   Updated: 2022/10/28 19:06:12 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	ft_bzero(char *str, unsigned int n)
{
	unsigned int	i;

	i = 0;
	while (i < n)
	{
		str[i] = 0;
		i++;
	}
}
