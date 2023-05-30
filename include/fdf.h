/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                             :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:09:59 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/30 14:40:55 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <MLX42/MLX42.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

#define WIDTH 1024
#define HEIGHT 720

#define TITLE "Super awesome lines bruv"

#define COLOR_BACKGROUND 0x333333FF
#define COLOR_POINT_DEFAULT 0x00AACFFF



typedef struct s_mat3x3
{
	float data[3][3];
} t_mat3x3;

typedef struct s_point
{
	float x;
	float y;
	float z;
	int32_t color;
}	t_point;

typedef struct s_node
{
	t_point 		point;
	struct s_node	*next;
}	t_node;

typedef struct s_map
{
	t_node *points_list;
	t_node *points_last;

	t_point *points;

	uint32_t width;
	uint32_t height;
}	t_map;

typedef struct s_projector
{
	float scalar;
	float amplitude;
	float angle_x;
	float angle_y;
	float angle_z;

} 	t_projector;

typedef struct s_fdf
{
	t_map *map;
	t_projector projector;

	mlx_t *mlx;
	mlx_image_t *image;
}	t_fdf;

typedef enum e_error
{
	ERR_ARGS_INVALID,
	ERR_MAP_INVALID,
	ERR_MALLOC_FAILURE,
	ERR_COUNT,
}	t_error;


const static char *ERROR_NAME[] = {
	[ERR_ARGS_INVALID] = "Usage: ./fdf <map>",
	[ERR_MAP_INVALID] = "Invalid map",
	[ERR_MALLOC_FAILURE] = "Malloc failure",
};


// fdf.c
int32_t		fdf(int32_t argc, const char* argv[]);

// parser.c
uint32_t 	parser(t_fdf *fdf, const char *map);

// utils.c
uint8_t		check_extension(const char *map, const char *ext);
uint32_t 	color_add_alpha(uint32_t c);
uint32_t	list_to_arr(t_fdf *fdf);
t_point matmul(t_point point, t_mat3x3 m);

// list.c
int		lstsize(t_node *lst);
t_node	*lstadd_back(t_node **lst, t_node *new);
t_node	*lstlast(t_node *lst);
t_node	*lstnew(t_point point);

// free.c
void	free_split(char **s_split);
void 	free_lst(t_node *lst);

// graphics.c
int32_t graphics_init(t_fdf *fdf);

// line.c
void line_draw(t_fdf *fdf, t_point p_start, t_point p_end);

// error.c
uint32_t	error_message(t_error err);
uint32_t 	error_print(const char *s);

// projector.c
t_point projector(t_fdf *fdf, t_point point);
void projector_init(t_fdf *fdf);

// keyinput.c
void key_hook(void *param);

// ui.c
void fps_hook(void *param);

// draw.c
void draw_hook(void *param);
void 	fdf_put_pixel(t_fdf *fdf, t_point p);

// matrices.c
t_mat3x3	get_matrix_rotate_y(float angle);
t_mat3x3	get_matrix_rotate_x(float angle);
t_mat3x3	get_matrix_rotate_z(float angle);
t_mat3x3	get_matrix_iso();
t_mat3x3	get_matrix_ortho();

// meuk.c
void print_point(t_point point);
void print_points(t_fdf *fdf);
void print_points_arr(t_fdf *fdf);

#endif
