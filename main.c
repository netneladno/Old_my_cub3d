#include <stdio.h>
#include <fcntl.h>
#include "mlx/mlx.h"
#include "cub3d.h"
#include <stdlib.h>
#include <unistd.h>






int		main(int argc, char **argv)
{
	void *mlx;
	void *win;

	char	map[1024][1024];
	char	*line;
	int		fd;
	int		ret = 1;
	int		i = 0;
	int		j = -1;
	int		x = 20;
	int		y = 20;

	fd = open(argv[1], O_RDONLY);
	while (ret)
	{
		ret = get_next_line(fd, &line);
		j=-1;
		while (line[++j])
		{
			map[i][j] = line[j];
		}
		printf("%s\n", map[i]);
		i++;
	}

//
//	mlx = mlx_init();
//	win = mlx_new_window(mlx, 500, 500, "my_mlx");
//
//	while (map[i])
//	{
//		while(map[i][j])
//		{
//			if (map[i][j] == '1')
//			{
//				mlx_pixel_put(mlx, win, x, y, 0x990099);
//				x++;
//			}
//			else
//				x++;
//			j++;
//		}
//		x = 20;
//		y++;
//		i++;
//	}
//	mlx_loop(mlx);
//	return (0);
}
