cmake_minimum_required(VERSION 3.5)
project(mlx)
set(CMAKE_C_FLAGS -O3)

file(GLOB src
        mlx_int_str_to_wordtab.c
        mlx_png.c
        mlx_rgb.c
        mlx_shaders.c
        mlx_xpm.c)
file(GLOB inc *.h)
add_library(mlx STATIC ${src} ${inc})