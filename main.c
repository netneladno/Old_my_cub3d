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
				prm.plrpos_y = BORDER + i * SCALE;
				prm.plrpos_x = BORDER + j * SCALE;
				prm.map[i][j] = '0';
			}

		}
		i++;
	}

	prm.mlx = mlx_init();
	prm.win = mlx_new_window(prm.mlx, RESOLUT_X, RESOLUT_Y, "my_mlx");
	prm.img.img = mlx_new_image(prm.mlx, RESOLUT_X, RESOLUT_Y);
	prm.img.addr = mlx_get_data_addr(prm.img.img, &prm.img.bits_per_pixel, &prm.img.line_length, &prm.img.endian);
	write_floor_sky(&prm);
	print_map(&prm);
	prnt_plr(&prm, 0xDC143C);

	mlx_hook(prm.win, 2, 0, key_handler, &prm);
	mlx_loop(prm.mlx);
}

void print_map(strct *prm)
{
	int i = 0;
	int j = 0;
	prm->x = BORDER;
	prm->y = BORDER;
	while (prm->map[i][j])
	{
		while(prm->map[i][j])
		{
			if (prm->map[i][j] == '1')
			{
				print_square_map(prm, 0xffffff);
				prm->x = prm->x + SCALE;

			}
			else
			{
				print_square_map(prm, 0x222222);
				prm->x = prm->x + SCALE;

			}
			j++;
		}
		j = 0;
		prm->x = BORDER;
		prm->y = prm->y + SCALE;
		i++;
	}


}

void print_square_map(strct *prm, int color)
{
	int x_init = prm->x;
	int y_init = prm->y;


	while(y_init <= prm->y + SCALE)
	{
		while (x_init <= prm->x + SCALE)
		{
			my_mlx_pixel_put(&prm->img, x_init, y_init, color);
			x_init++;
		}
		x_init = prm->x;
		y_init++;
	}
}

void            my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char    *dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int key_handler(int keycode, strct *prm)
{
	if (keycode == 13 || keycode == 126)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->plrpos_y = prm->plrpos_y + SPEED * sin(prm->angle);
		prm->plrpos_x = prm->plrpos_x + SPEED * cos(prm->angle);

		printf("angle=%f\n", prm->angle * 180 / M_PI);
		printf("SPEED * sin(prm->angle)=%f\n", SPEED * sin(prm->angle));
		printf("SPEED * cos(prm->angle)=%f\n", SPEED * cos(prm->angle));
		prnt_plr(prm, 0xDC143C);
	}
	if (keycode == 1 || keycode == 125)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->plrpos_y = prm->plrpos_y - SPEED * sin(prm->angle);
		prm->plrpos_x = prm->plrpos_x - SPEED * cos(prm->angle);
		printf("angle=%f\n", prm->angle * 180 / M_PI);
		printf("SPEED * sin(prm->angle)=%f\n", SPEED * sin(prm->angle));
		printf("SPEED * cos(prm->angle)=%f\n", SPEED * cos(prm->angle));
		prnt_plr(prm, 0xDC143C);
	}
	if (keycode == 0)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->plrpos_y = prm->plrpos_y + SPEED * cos(prm->angle);
		prm->plrpos_x = prm->plrpos_x - SPEED * sin(prm->angle);
		prnt_plr(prm,0xDC143C);
	}
	if (keycode == 2)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->plrpos_y = prm->plrpos_y - SPEED * cos(prm->angle);
		prm->plrpos_x = prm->plrpos_x + SPEED * sin(prm->angle);
		prnt_plr(prm, 0xDC143C);
	}
	if (keycode == 124)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->angle = prm->angle + 0.05;
		prnt_plr(prm, 0xDC143C);

	}
	if (keycode == 123)
	{
		mlx_clear_window(prm->mlx, prm->win);
		mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);
		prm->angle = prm->angle - 0.05;
		prnt_plr(prm, 0xDC143C);

	}





	if (keycode == 53)
	{
		mlx_destroy_window(prm->mlx, prm->win);
		exit(0);
	}

	return (1);
}



void prnt_plr (strct *prm, int color)
{
	int y_init = prm->plrpos_y;
	int x_init = prm->plrpos_x;

	while(y_init <= prm->plrpos_y + SCALE)
	{
		while (x_init <= prm->plrpos_x + SCALE)
		{
			mlx_pixel_put(prm->mlx, prm->win, x_init, y_init, color);
			x_init++;
		}
		x_init = prm->plrpos_x;
		y_init++;
	}
	print_ray(prm, 0x574963);


	print3d (prm, 0x574963);
}


void print_ray(strct *prm, int color)
{
	float ray_y;
	float ray_x;
	int i = 0;
	int raylen = 0;
	float angle = prm->angle - 0.5;

	while (angle < prm->angle + 0.5)
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
//		printline(prm, i, 10*RESOLUT_Y/raylen, 0x759852);
		prm->rays[i] = raylen;
		i++;
		angle = angle + 1 / (float)RESOLUT_X;
	}
}

void print3d (strct *prm, int color)
{
	int len = 0;
	int x = 0;
	while (x < (int)RESOLUT_X)
	{

		len = 10*RESOLUT_Y/prm->rays[x];
//		printf("x=%d, len=%d\n", x, len);
		printline(prm, x, len, 0x759852);

		x++;
	}

}

void printline (strct *prm, int x, int len, int color)
{
	int i = 0;
	int y = (int)RESOLUT_Y/2 - len/2;
	while (i <= len)
	{
		mlx_pixel_put(prm->mlx, prm->win, x, y, color);
		y++;
		i++;
	}
}

void   write_floor_sky(strct *prm)
{
	int x;
	int y = -1;

	while (++y< RESOLUT_Y/2-1)
	{
		x = -1;
		while(++x< RESOLUT_X-1)
		{
			my_mlx_pixel_put(&prm->img, x, y, 0x00BFFF);
		}
	}
	while (++y<RESOLUT_Y)
	{
		x = -1;
		while(++x< RESOLUT_X-1)
		{
			my_mlx_pixel_put(&prm->img, x, y, 0x654321 );
		}
	}
}