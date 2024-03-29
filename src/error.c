/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 21:17:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/27 15:20:20 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static const char	*g_error_names[] = {\
	[ERR_ARGS_INVALID] = "Usage: ./fdf <map>",	\
	[ERR_MAP_INVALID] = "Invalid map",			\
	[ERR_MALLOC_FAILURE] = "Malloc failure",	\
};

uint32_t	error_message(t_error err)
{
	return (error_print(g_error_names[err]));
}

uint32_t	error_print(const char *s)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
