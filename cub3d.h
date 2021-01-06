
#ifndef CUB3D_CUB3D_H
#define CUB3D_CUB3D_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
#include <unistd.h>
#include <stdlib.h>
#define SCALE 30
#define SPEED 7

typedef struct s_mlx
{
	void 	*mlx;
	void 	*win;
	int 	x;
	int 	y;
	char	map[1024][1024];
	int 	plrpos_x;
	int		plrpos_y;
}	strct;


int		get_next_line(int fd, char **line);
size_t	ft_strlen(const char *s);
char	*ft_strdup(const char *s1);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strcpy(char *dest, char *src);
void 	print_map(strct prm);
int key_handler(int keycode, strct *prm);
void print_square(strct prm, int color);
void prnt_plr (strct prm, int color);





# endif //CUB3D_CUB3D_H
# endif //CUB3D_CUB3D_H