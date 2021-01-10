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

	prm.x = BORDER;
	prm.y = BORDER;
	prm.angle = 0;


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
//				printf("%d %d", i, j);
				prm.plrpos_y = BORDER + i * SCALE;
				prm.plrpos_x = BORDER + j * SCALE;
				prm.map[i][j] = '0';
			}

		}
//		printf("%s\n", prm.map[i]);
		i++;
	}

	prm.mlx = mlx_init();
	prm.win = mlx_new_window(prm.mlx, RESOLUT_X, RESOLUT_Y, "my_mlx");
	print_map(prm);
	prnt_plr(prm, 0xDC143C);

	mlx_hook(prm.win, 2, 0, key_handler, &prm);
	mlx_loop(prm.mlx);
}

void print_map(strct prm)
{
	int i = 0;
	int j = 0;
	prm.x = BORDER;
	prm.y = BORDER;
	while (prm.map[i][j])
	{
		while(prm.map[i][j])
		{
			if (prm.map[i][j] == '1')
			{
				print_square(prm, 0xffffff);
				prm.x = prm.x + SCALE;

			}
			else
			{
				print_square(prm, 0x222222);
				prm.x = prm.x + SCALE;

			}
//			prm.x = prm.x + 2;
			j++;
		}
		j = 0;
		prm.x = BORDER;
		prm.y = prm.y + SCALE;
//		prm.y = prm.y + 2;
		i++;
	}
//	printf("\n%d %d", prm.y, prm.x);


}

void prnt_plr (strct prm, int color)
{
		int y_init = prm.plrpos_y;
		int x_init = prm.plrpos_x;
//		printf("\n%d %d", prm.plrpos_y, prm.plrpos_x);

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
		print_ray(prm, 0x574963);
}

int key_handler(int keycode, strct *prm)
{
//	printf("keycode = %d\n", keycode);
	if (keycode == 13)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_y = prm->plrpos_y - SPEED;
		prnt_plr(*prm, 0xDC143C);
	}
	if (keycode == 1)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_y = prm->plrpos_y + SPEED;
		prnt_plr(*prm, 0xDC143C);
	}
	if (keycode == 0)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_x = prm->plrpos_x - SPEED;
		prnt_plr(*prm, 0xDC143C);
	}
	if (keycode == 2)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->plrpos_x = prm->plrpos_x + SPEED;
		prnt_plr(*prm, 0xDC143C);
	}
	if (keycode == 124)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->angle = prm->angle + 0.05;
		prnt_plr(*prm, 0xDC143C);

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

void print_ray(strct prm, int color)
{
	float ray_y = (float)prm.plrpos_y + SCALE/2;
	float ray_x = (float)prm.plrpos_x + SCALE/2;
	int raylen = 0;

	float angle = prm.angle;

	while (angle < prm.angle + 1)
	{
		ray_y = (float)prm.plrpos_y + SCALE/2;
		ray_x = (float)prm.plrpos_x + SCALE/2;

		while (raylen < 1000)
		{
			ray_y = ray_y + sin(angle);
			ray_x = ray_x + cos(angle);
			if (prm.map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] != '1')
				mlx_pixel_put(prm.mlx, prm.win, (int)ray_x, (int)ray_y, color);
			else
				break;
			raylen++;
		}
		raylen = 0;



		angle = angle + 0.015;
	}



}

