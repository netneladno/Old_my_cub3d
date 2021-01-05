cmake_minimum_required(VERSION 3.17)
project(cub3d C)

set(CMAKE_C_STANDARD 99)

add_executable(cub3d main.c cub3d.h get_next_line.c get_next_line_utils.c)