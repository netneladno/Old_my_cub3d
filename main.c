#include <stdio.h>
#include <fcntl.h>
#include "mlx/mlx.h"
#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>


int		main(int argc, char **argv)
{
	strct prm;
	char *line;
	int fd;
	int ret = 1;
	int i = 0;
	int j;

	prm.x = 20;
	prm.y = 20;

	fd = open(argv[1], O_RDONLY);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		j = -1;
		while (line[++j])
		{
			prm.map[i][j] = line[j];
			if (prm.map[i][j] == 'N')
			{
				prm.plrpos_y = i * SCALE;
				prm.plrpos_x = j * SCALE;
				prm.map[i][j] = '0';
			}

		}
		printf("%s\n", prm.map[i]);
		i++;
	}

	prm.mlx = mlx_init();
	prm.win = mlx_new_window(prm.mlx, 1100, 1000, "my_mlx");
	print_map(prm);
	prnt_plr(prm, 0x435345);

	mlx_hook(prm.win, 2, 0, key_handler, &prm);
	mlx_loop(prm.mlx);
}

void print_map(strct prm)
{
	int i = 0;
	int j = 0;
	prm.x = 20;
	prm.y = 20;
	while (prm.map[i][j])
	{
		while(prm.map[i][j])
		{
			if (prm.map[i][j] == '1')
			{
				print_square(prm, 0xffffff);

//				printf("prm.x = %d\n", prm.x);
				prm.x = prm.x + SCALE;

			}
			else
			{
				print_square(prm, 0x808080);
				prm.x = prm.x + SCALE;

			}

			j++;
		}
		j = 0;
		prm.x = 20;
		prm.y = prm.y + SCALE;
		prm.y++;
		printf("prm.y = %d\n", prm.y);
		i++;
	}


}

void prnt_plr (strct prm, int color)
{
		int y_init = prm.plrpos_y;
		int x_init = prm.plrpos_x;



		while(y_init <= prm.plrpos_y + SCALE)
		{
			while (x_init <= prm.plrpos_x + SCALE)
			{
				mlx_pixel_put(prm.mlx, prm.win, x_init, y_init, color);
				x_init++;
			}
			x_init = prm.plrpos_x;
			y_init++;
		}
}

int key_handler(int keycode, strct *prm)
{
	printf("keycode = %d\n", keycode);
	if (keycode == 13)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_y = prm->plrpos_y - SPEED;
		prnt_plr(*prm, 0x435345);
	}
	if (keycode == 1)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_y = prm->plrpos_y + SPEED;
		prnt_plr(*prm, 0x435345);
	}
	if (keycode == 0)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_x = prm->plrpos_x - SPEED;
		prnt_plr(*prm, 0x435345);
	}
	if (keycode == 2)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_x = prm->plrpos_x + SPEED;
		prnt_plr(*prm, 0x435345);
	}
	if (keycode == 53)
	{
		mlx_destroy_window(prm->mlx, prm->win);
		exit(0);
	}

	return (1);
}

void print_square(strct prm, int color)
{
	int x_init = prm.x;
	int y_init = prm.y;


	while(y_init <= prm.y + SCALE)
	{
		while (x_init <= prm.x + SCALE)
		{
			mlx_pixel_put(prm.mlx, prm.win, x_init, y_init, color);
			x_init++;
		}
		x_init = prm.x;
		y_init++;
	}
}



