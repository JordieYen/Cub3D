#include "cube3d.h"
#include "libft/libft.h"
#include <stdio.h>

int	darken_rgb(int rgb, float percentage)
{
	int value;

	value = (int)rgb - (rgb * percentage);
	if (value < 0)
		value = 0;
	if (value > 255)
		value = 255;
	return (value);
}

void create_shadows(t_map *map, int ray_num)
{
	int i;
	char *red;
	char *blue;
	char *green;
	char *temp;

	i = -1;
	while(++i < ray_num)
	{
		if (map->rays[i].xmin == 0)
		{
			map->rays[i].rgb.red = 61;
			map->rays[i].rgb.green = 10; 
			map->rays[i].rgb.blue = 229;

		}
		if (map->rays[i].xmin == 1)
		{
			map->rays[i].rgb.red = 14;
			map->rays[i].rgb.green = 24; 
			map->rays[i].rgb.blue = 165;
		}
		map->rays[i].rgb.red = darken_rgb(map->rays[i].rgb.red, 0.003 * map->rays[i].len);
		map->rays[i].rgb.green = darken_rgb(map->rays[i].rgb.green, 0.003 * map->rays[i].len);
		map->rays[i].rgb.blue = darken_rgb(map->rays[i].rgb.blue, 0.003 * map->rays[i].len);
		red = ft_itoh(map->rays[i].rgb.red);
		green = ft_itoh(map->rays[i].rgb.green);
		blue = ft_itoh(map->rays[i].rgb.blue);
		if (ft_strlen(red) == 1)
		{
			temp = ft_strdup("0");
			temp = ft_strjoin(temp, red);
			red = temp;
		}
		if (ft_strlen(green) == 1)
		{
			temp = ft_strdup("0");
			temp = ft_strjoin(temp, green);
			green = temp;
		}
		if (ft_strlen(blue) == 1)
		{
			temp = ft_strdup("0");
			temp = ft_strjoin(temp, blue);
			blue = temp;
		}
		red = ft_strjoin(red, green);
		red = ft_strjoin(red, blue);
		map->rays[i].rgb_str = ft_strdup(red);
		free(red);
		free(green);
		free(blue);
	}
	
}