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
				print_square_map(prm, 0xffffff);
				prm.x = prm.x + SCALE;

			}
			else
			{
				print_square_map(prm, 0x222222);
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

void print_square_map(strct prm, int color)
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
	if (keycode == 123)
	{
		mlx_clear_window(prm->mlx, prm->win);
		print_map(*prm);
		prm->angle = prm->angle - 0.05;
		prnt_plr(*prm, 0xDC143C);

	}





	if (keycode == 53)
	{
		mlx_destroy_window(prm->mlx, prm->win);
		exit(0);
	}

	return (1);
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
		print_ray(&prm, 0x574963);

	int i = 0;

//		print3d (prm, 0x574963);
}


void print_ray(strct *prm, int color)
{
	float ray_y;
	float ray_x;
	int i = 0;
	int raylen = 0;
	float angle = prm->angle;

//	while (i <= 100)
//	{
//		prm.rays[i] = 0;
//		i++;
//	}
//	i = 0;

	while (angle < prm->angle + 1)
	{
		ray_y = (float)prm->plrpos_y + SCALE/2;
		ray_x = (float)prm->plrpos_x + SCALE/2;

		raylen = 0;
		while (raylen < 1000)
		{
			ray_y = ray_y + sin(angle);
			ray_x = ray_x + cos(angle);
			if (prm->map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] != '1')
				mlx_pixel_put(prm->mlx, prm->win, (int)ray_x, (int)ray_y, color);
			else
				break;
			raylen++;
		}
		prm->rays[i] = raylen;
//		print_square(prm, 550-((1/raylen)*1000), 3i, 3, (1/raylen)*1000, 0x862578);

		//		print_square(prm, 550-(1/prm.rays[i]*100/2), 3i, 3, 1/prm.rays[i]*100, 0x862578);
//		printf ("prm.rays[%d]=%d\n", i, prm.rays[i]);

		i++;
//		printf ("raylen=%d\n", raylen);



		angle = angle + 0.015;
	}

//	i = 0;
//	while (i <= 66)
//	{
//		printf ("prm->rays[%d]=%d\n", i,  prm->rays[i]);
//		i++;
//	}
}



//
//void print3d (strct prm, int color)
//{
//	int i = 0;
//	while (i <= 66)
//	{
//		i = 0;
//		while (i <= 100)
//		{
//			printf ("%d\n", prm.rays[i]);
//			i++;
//		}
////		printf ("prm.rays[%d]=%d\n", i, prm.rays[i]);
////		print_square(prm, 550-(1/prm.rays[i]*100/2), 3i, 3, 1/prm.rays[i]*100, color);
//		i++;
//	}
//
//
//}



void print_square(strct prm, int y, int x, int width, int height, int color)
{
	int y_init = y;
	int x_init = x;

	while(y_init <= y + height)
	{
		while (x_init <= x + width)
		{
			mlx_pixel_put(prm.mlx, prm.win, x_init, y_init, color);
			x_init++;
		}
		x_init = x;
		y_init++;
	}
}