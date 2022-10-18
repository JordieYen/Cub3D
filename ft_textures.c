#include "cube3d.h"
#include <stdio.h>
#include "libmlx/mlx.h"

void	create_line_colors(t_map *map, int ray_num)
{
	int	i;
	char *data;
	int	bits_per_pixel;
	int	size_line;
	int	endian;
	int rgb_val;
	int j;

	// int	column;
	// int	row;

	// column = -1; needs to be determined by where the ray hit
	// row = -1; needs to be determined by where the ray hit
	i = -1;

	printf("%d\n", ray_num);
	printf("%d\n", map->wall_height);
	printf("%d\n", map->wall_width);
	data = mlx_get_data_addr(map->wall, &bits_per_pixel, &size_line, &endian);
	printf("BPP %d\n", bits_per_pixel);
	int max;
	max = 0;
	// max  = sizeof(data) / (bits_per_pixel / 8) ;
	printf("ayy %d\n", max);
	while (++i < (map->wall_width * map->wall_height))
	{
		j = 0;
		rgb_val = 0;
		// while (j < 4)
		// {
		// 	rgb_val += data[i * 4 + j];
		// 	j++;
		// }
		max += sizeof(data[i]);
		printf("%x",data[i]);
	}
	printf("aaaayy %d\n", max);
}
