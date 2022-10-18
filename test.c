#include "libmlx/mlx.h"
#include <stdio.h>

int	main(void)
{
	void	*mlx;
	void	*img;
	char	*relative_path = "./cyber.xpm";
	int		img_width;
	int		img_height;
	int		*rgb_val;
	int		i;
	char	*str;
	int		bpp;
	int		tempx;
	int		tempy;

	i = -1;
	mlx = mlx_init();
	img = mlx_xpm_file_to_image(mlx, relative_path, &img_width, &img_height);
	str = mlx_get_data_addr(img, &bpp, &tempx, &tempy);
	while (++i < (img_width * img_height) - 1)
		printf("%x", str[i]);
	printf("width: %d height: %d\n", img_width, img_height);
}