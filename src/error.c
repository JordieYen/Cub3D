/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:24:37 by jking-ye          #+#    #+#             */
/*   Updated: 2022/11/01 16:09:12 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"
#include <stdlib.h>
#include <fcntl.h>
#include "../includes/libft.h"
#include <unistd.h>
#include "../includes/get_next_line.h"
#include <math.h>
#include <limits.h>
#include <stdio.h>

void	error_exit(char *error)
{
	ft_putstr_fd(error, 2);
	system("leaks cub3D");
	exit(2);
}

void	check_wall_dir(char **tex, char *dir)
{
	if (*tex == NULL)
		*tex = ft_strdup(dir);
	else
		error_exit("Error: double key\n");
}
