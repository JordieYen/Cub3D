#include "cube3d.h"
#include "libmlx/mlx.h"
#include <stdio.h>
#include <math.h>

void move_player(t_map *map, int key)
{
	if (key == E)
		handledoors(map);
	if (key == S)
	{
		if (map->coord[(int)(map->player->y - map->player->dy)][(int)(map->player->x - map->player->dx)] != '1'
			&& map->coord[(int)(map->player->y - map->player->dy)][(int)(map->player->x - map->player->dx)] != 'C')
		{
			map->player->x -= map->player->dx;
			map->player->y -= map->player->dy;
		}
	}
	if (key == W)
	{
		if (map->coord[(int)(map->player->y + map->player->dy * 2)][(int)(map->player->x + map->player->dx * 2)] != '1'
			&& map->coord[(int)(map->player->y + map->player->dy * 2)][(int)(map->player->x + map->player->dx * 2)] != 'C')
		{
			map->player->x += map->player->dx;
			map->player->y += map->player->dy;
		}
	}
}

int	deal_key(int key, t_map *map)
{
	if (key == W || key == A || key == E)
		move_player(map, key);
	return (0);
}

int read_mouse(int x, int y, t_map *map)
{
    int dir;
    (void) y;

    dir = 100 - x;
    mlx_mouse_move(map->win, 100, 100);
    if (dir < 0)
    {
        map->player->angle += DR * (dir * -1 / 2);
        if (map->player->angle > 2 * PI)
            map->player->angle = map->player->angle - 2 * PI;
        map->player->dx = cos(map->player->angle) / 10;
        map->player->dy = sin(map->player->angle) / 10;
    }
    if (dir > 0)
    {
        map->player->angle -= DR * (dir / 2);
	    if (map->player->angle < 0)
	    	map->player->angle = map->player->angle + 2 * PI;
	    map->player->dx = cos(map->player->angle) / 10;
	    map->player->dy = sin(map->player->angle) / 10;
    }
	return (0);
}

