/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jking-ye <jking-ye@student.42kl.edu.my>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/16 16:14:09 by jking-ye          #+#    #+#             */
/*   Updated: 2022/04/17 14:40:27 by jking-ye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	drawgrid(t_cartesian *chart, t_data *img, int color)
{
	t_coord	count;

	init_coord(&count, 0, 0, 0);
	while (count.y < (chart->ylen))
	{
		count.x = 0;
		while (count.x < (chart->xlen))
		{
			if (count.x + 1 != chart->xlen)
				connectdots(img, chart->coords[count.y][count.x],
					chart->coords[count.y][count.x + 1], color);
			if (count.y + 1 != chart->ylen)
				connectdots(img, chart->coords[count.y][count.x],
					chart->coords[count.y + 1][count.x], color);
			count.x++;
		}
		count.y++;
	}
}

int	closer(int keycode, t_vars *vars)
{
	(void)vars;
	(void)keycode;
	exit(1);
}

int	key_hook(int keycode, t_vars *vars)
{
	(void)vars;
	(void)keycode;
	if (keycode == 53)
	{
		mlx_destroy_window(vars->mlx, vars->win);
		exit(1);
	}
	return (0);
}

void	fdf(t_cartesian *chart)
{
	t_vars	vars;
	t_data	img;
	t_coord	center;

	vars.mlx = mlx_init();
	vars.win = mlx_new_window(vars.mlx, 1920, 1080, "FDF IS SO COOL");
	img.img = mlx_new_image(vars.mlx, 1920, 1080);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
			&img.line_length, &img.endian);
	vars.img = &img;
	vars.chart = chart;
	init_coord(&center, 0, 0, 0);
	center.x = (chart->coords[0][chart->xlen - 1].x / 2)
		+ chart->coords[0][0].x;
	center.y = (chart->coords[chart->ylen - 1][0].y / 2)
		+ chart->coords[0][0].y;
	rotatechart(&img, chart, center);
	mlx_put_image_to_window(vars.mlx, vars.win, img.img, 0, 0);
	mlx_hook(vars.win, 17, 0, closer, &vars);
	mlx_hook(vars.win, 3, 0L, key_hook, &vars);
	mlx_loop(vars.mlx);
}

int	main(int argc, char **argv)
{
	int			fd;
	t_coord		len;
	t_cartesian	chart;
	char		*temp;

	if (argc != 2)
		return (0);
	fd = open(argv[1], O_RDONLY);
	init_coord(&len, countxlen(get_next_line(fd)), 1, 0);
	temp = get_next_line(fd);
	while (temp != NULL)
	{
		free(temp);
		temp = get_next_line(fd);
		len.y++;
	}
	close(fd);
	init_cartesian(&chart, len.x, len.y);
	get_z(&chart, argv[1], len.x, len.y);
	get_x(&chart, 0, 1920 / (len.x * 2));
	get_y(&chart, 0, 1920 / (len.x * 2));
	fdf(&chart);
	freechart(&chart);
	return (0);
}
