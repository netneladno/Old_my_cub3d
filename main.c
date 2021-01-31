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

	prm.x = 0;
	prm.y = 0;
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
				prm.plrpos_y = i * SCALE;
				prm.plrpos_x = j * SCALE;
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
	prm->x = 0;
	prm->y = 0;
	while (prm->map[i][j])
	{
		while(prm->map[i][j])
		{
			if (prm->map[i][j] == '1')
				prm->x = prm->x + SCALE;

			else
			{
				prm->x = prm->x + SCALE;

			}
			j++;
		}
		j = 0;
		prm->x = 0;
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
	int old_x = prm->plrpos_x;
	int old_y = prm->plrpos_y;

	if (keycode == 13 || keycode == 126)
	{
		prm->plrpos_y = prm->plrpos_y + SPEED * sin(prm->angle);
		prm->plrpos_x = prm->plrpos_x + SPEED * cos(prm->angle);
	}
	if (keycode == 1 || keycode == 125)
	{

		prm->plrpos_y = prm->plrpos_y - SPEED * sin(prm->angle);
		prm->plrpos_x = prm->plrpos_x - SPEED * cos(prm->angle);


	}
	if (keycode == 0)
	{
		prm->plrpos_y = prm->plrpos_y - SPEED * cos(prm->angle);
		prm->plrpos_x = prm->plrpos_x + SPEED * sin(prm->angle);
	}
	if (keycode == 2)
	{
		prm->plrpos_y = prm->plrpos_y + SPEED * cos(prm->angle);
		prm->plrpos_x = prm->plrpos_x - SPEED * sin(prm->angle);
	}
	if (keycode == 124)
	{

		prm->angle = prm->angle + 0.05;


	}
	if (keycode == 123)
	{

		prm->angle = prm->angle - 0.05;


	}

	if (keycode == 53)
	{
		mlx_destroy_window(prm->mlx, prm->win);
		exit(0);
	}
//	printf("%c\n", prm->map[(int)((prm->plrpos_y + SCALE/2) / SCALE)][(int)((prm->plrpos_x + SCALE/2) / SCALE)]);

	if (prm->map[(int)((prm->plrpos_y + SCALE/2) / SCALE)][(int)((prm->plrpos_x + SCALE/2) / SCALE)] != '0')

	{
		printf("done\n");

		prm->plrpos_y = old_y;
		prm->plrpos_x = old_x;
	}

	mlx_destroy_image(prm->mlx, prm->img.img);
	mlx_clear_window(prm->mlx, prm->win);
	prm->img.img = mlx_new_image(prm->mlx, RESOLUT_X, RESOLUT_Y);
	prm->img.addr = mlx_get_data_addr(prm->img.img, &prm->img.bits_per_pixel, &prm->img.line_length, &prm->img
			.endian);
	prnt_plr(prm, 0xDC143C);
	mlx_put_image_to_window(prm->mlx, prm->win, prm->img.img, 0, 0);






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
//			mlx_pixel_put(prm->mlx, prm->win, x_init, y_init, color);
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
	float raylen = 0;
	float angle = prm->angle - 0.5;
	float angle_sin = 0;
	float angle_cos = 0;
	int ray_y_prev = 0;
	int ray_x_prev = 0;



	while (angle < prm->angle + 0.5)
	{
		ray_y = prm->plrpos_y + SCALE/2;
		ray_x = prm->plrpos_x + SCALE/2;

		raylen = 0;

		angle_sin = sin(angle);
		angle_cos = cos(angle);
		while (raylen < RESOLUT_X)
		{
			ray_y = ray_y + angle_sin;
			ray_x = ray_x + angle_cos;
			if (prm->map[(int)(ray_y / SCALE)][(int)(ray_x / SCALE)] == '1')
				break;
			raylen += 0.1;
		}
		ray_y_prev = (ray_y - angle_sin);
		ray_x_prev = (ray_x - angle_cos);
		if (ray_x_prev == (int)ray_x && ray_y_prev > (int)ray_y)
			prm->ray_side[i] = 1;
		else if (ray_x_prev == (int)ray_x && ray_y_prev > (int)ray_y)
			prm->ray_side[i] = 2;
		else if (ray_x_prev > (int)ray_x && ray_y_prev == (int)ray_y)
			prm->ray_side[i] = 3;
		else
//			(ray_x_prev < (int)ray_x && ray_y_prev == (int)ray_y)
			prm->ray_side[i] = 4;
		prm->rays[i] = raylen*cos(prm->angle - angle) ;
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

		len = 40*RESOLUT_Y/prm->rays[x]; // если уменьшить 40 - можно освободить ресурсы
		printf("x=%d, prm->ray_side[x]=%d\n", x, prm->ray_side[x]);
		if (prm->ray_side[x] = 1)
			printline(prm, x, len, 0x759852);
		else if (prm->ray_side[x] = 2)
			printline(prm, x, len, 0xff0000);
		else if (prm->ray_side[x] = 3)
			printline(prm, x, len, 0x800080);
		else
//			(prm->ray_side[x] = 4)
			printline(prm, x, len, 0x281e5d);



		x++;
	}

}

void printline (strct *prm, int x, int len, int color)
{
	int y = 0;

//	int y = (int)RESOLUT_Y/2 - len/2;

	while (y <= (int)RESOLUT_Y/2 - len/2 )
	{
		if (y > 0)
			my_mlx_pixel_put(&prm->img, x, y, 0x00BFFF);
		y++;

	}

	while (y <= (int)RESOLUT_Y/2 + len/2 )
	{
		if (y > 0)
			my_mlx_pixel_put(&prm->img, x, y, color);
		y++;

	}

	while (y < (int)RESOLUT_Y )
	{
		if (y > 0)
			my_mlx_pixel_put(&prm->img, x, y, 0x654321);
		y++;

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