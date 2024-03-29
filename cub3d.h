
#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#include <unistd.h>
#include <stdlib.h>
#include <math.h>
#define SCALE 300
#define SPEED 100
#define RESOLUT_X 2560
#define RESOLUT_Y 1440


typedef struct	s_data
{
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;


typedef struct s_mlx
{
	void 		*mlx;
	void 		*win;
	int 		x;
	int 		y;
	char		map[1024][1024];
	int 		plrpos_x;
	int			plrpos_y;
	float 		angle;
	float		rays[RESOLUT_X];
	t_data		img;
	int			ray_side[RESOLUT_X]

}	strct;


int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *s);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strcpy(char *dest, char *src);
void			print_map(strct *prm);
int				key_handler(int keycode, strct *prm);
void			print_square_map(strct *prm, int color);
void			prnt_plr (strct *prm, int color);
void			print_ray(strct *prm, int color);
void			print_square(strct *prm, int y, int x, int width, int height, int color);
void			print3d (strct *prm, int color);
void			printline (strct *prm, int x, int len, int color);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
void			write_floor_sky(strct *prm);
int drawing(strct *prm);






# endif //CUB3D_CUB3D_H
# endif //CUB3D_CUB3D_H