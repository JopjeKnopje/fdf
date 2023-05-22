/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                             :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:09:59 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/22 16:18:31 by jboeve        ########   odam.nl         */
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

#define COLOR_BACKGROUND 0x000000FF
#define COLOR_POINT_DEFAULT 0x00AACFFF


typedef struct s_point
{
	uint32_t x;
	uint32_t y;
	uint32_t z;
	uint32_t color;
}	t_point;

typedef struct s_node
{
	t_point 		point;
	struct s_node	*next;
}	t_node;

typedef struct s_map
{
	t_node *points;
	t_node *points_last;

	uint32_t width;
	uint32_t height;

}	t_map;

typedef struct s_fdf
{
	t_map *map;

	int32_t scalar;
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

// projector.c
void projector_iso(uint32_t *x, uint32_t *y, uint32_t scalar);

// error.c
uint32_t	error_message(t_error err);
uint32_t 	error_print(const char *s);



// meuk.c
void print_point(t_point point);
void print_points(t_fdf *fdf);

#endif
