/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                              :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:09:59 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/17 09:20:15 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "libft.h"
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct s_point
{

}	t_point;

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
	"Usage: ./fdf <map>",
	"Invalid map",
};


// error.c
uint32_t	error_message(t_error err);
uint32_t 	error_print(const char *s);

uint32_t 	parser(const char *map);

#endif
