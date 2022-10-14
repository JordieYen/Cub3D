
int	color;
while (++i < ray_num)
{
	j = -1;
	color = 0xFFFFFF;
	while (j++ < 1080)
	{
		put_p(map->img, i, j, color);
		if (j < 504 && j > 300 && color - 0x010101 > 0)
			color = color - 0x010101;
		if (j > 504 && j < 700  && color + 0x010101 < 0xFFFFFF)
			color = color + 0x010101;
		// if (i == 0)
		// 	printf("color = %d\n", color);
	}
}

// int	darken(int color)
// {
// 	int darkened;
// 	int	red;
// 	int	green;
// 	int	blue;

// 	if (color > 0xFF)
// 	{
// 		blue = color / 256;
// 		if (color > 0xFFFF)
// 		{
// 			green = color / 16;
// 			if (color > 0xFFFFFF)
// 				darkened -= 0x01;
// 		}
// 	}
// }