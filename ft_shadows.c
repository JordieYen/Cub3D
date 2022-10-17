#include "cube3d.h"
#include "libft/libft.h"
#include <stdio.h>

void create_shadows(t_map *map, int ray_num)
{
	int i;
	char *red;
	char *blue;
	char *green;

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
		printf("1oo\n");
		red = ft_itoh(map->rays[i].rgb.red);
		green = ft_itoh(map->rays[i].rgb.green);
		blue = ft_itoh(map->rays[i].rgb.blue);
		printf("%s %s %s\n", red, green, blue);
		printf("o2o\n");
		ft_strjoin(red, green);
		ft_strjoin(red, blue);
		printf("RGB %s\n", red);
		map->rays[i].rgb_str = ft_strdup(red);
		free(red);
		free(green);
		free(blue);
		printf("oo\n");
	}
	
}