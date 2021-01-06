#include <stdio.h>
#include <fcntl.h>
#include "mlx/mlx.h"
#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>

int key_handler(int keycode, strct *prm)
{
//	printf("keycode = %d\n", keycode);
if (keycode == 1)
{

}


if (keycode == 53)
	{
		mlx_destroy_window(prm->mlx, prm->win);
		exit(0);
	}

	return (1);
}

void print_square(strct prm)
{
	int x_init = prm.x;
	int y_init = prm.y;


	while(y_init <= prm.y + 30)
	{
		while (x_init <= prm.x + 30)
		{
			mlx_pixel_put(prm.mlx, prm.win, x_init, y_init, 0xffffff);
			x_init++;
		}
		x_init = prm.x;
		y_init++;
	}
}


int		main(int argc, char **argv)
{


	strct 	prm;
	char	*line;
	int		fd;
	int		ret = 1;
	int		i = 0;
	int		j = -1;

	prm.x = 20;
	prm.y = 20;

	fd = open(argv[1], O_RDONLY);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		j=-1;
		while (line[++j])
		{
			prm.map[i][j] = line[j];
		}
		printf("%s\n", prm.map[i]);
		i++;
	}

	prm.mlx = mlx_init();
	prm.win = mlx_new_window(prm.mlx, 1100, 1000, "my_mlx");

	i = 0;
	j = 0;
	while (prm.map[i][j])
	{
		while(prm.map[i][j])
		{
			if (prm.map[i][j] == '1')
			{
//				mlx_pixel_put(prm.mlx, prm.win, prm.x, prm.y, 0xffffff);
				print_square(prm);
				prm.x = prm.x + 30;
			}
			else
				prm.x = prm.x + 30;
			j++;
		}
		j = 0;
		prm.x = 20;
		prm.y = prm.y + 30;;
		i++;
	}
	mlx_hook(prm.win, 2, 0, key_handler, &prm);
	mlx_loop(prm.mlx);
	return (0);
}
