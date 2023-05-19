/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                             :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:09:59 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/20 00:06:05 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef union s_color
{
	unsigned int      c;
	struct s_rgba 
	{
		uint8_t b;
		uint8_t g;
		uint8_t r;
		uint8_t a;
	} rgba;
} t_color;

typedef struct s_point
{
	uint32_t x;
	uint32_t y;
	t_color color;
}	t_point;

typedef struct s_node
{
	t_point 		*point;
	struct s_node	*next;
}	t_node;

typedef struct s_fdf
{
	t_point *points;
}	t_fdf;

typedef enum e_error
{
	ERR_ARGS_INVALID,
	ERR_MAP_INVALID,
	ERR_COUNT,
}	t_error;


const static char *ERROR_NAME[] = {
	[ERR_ARGS_INVALID] = "Usage: ./fdf <map>",
	[ERR_MAP_INVALID] = "Invalid map",
};


// fdf.c
int32_t		fdf(int32_t argc, const char* argv[]);

// parser.c
uint32_t 	parser(t_fdf *fdf, const char *map);

// utils.c
uint8_t		check_extension(const char *map, const char *ext);

// list.c
int	lstsize(t_node *lst);
void	lstadd_back(t_node **lst, t_node *new);
t_node	*lstlast(t_node *lst);
t_node	*lstnew(void *point);
void	lstclear(t_node **lst, void (*del)(void*));

// error.c
uint32_t	error_message(t_error err);
uint32_t 	error_print(const char *s);

#endif
