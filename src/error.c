/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 21:17:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/17 09:26:20 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


uint32_t	error_message(t_error err)
{
	return (error_print(ERROR_NAME[err]));
}

// TODO Maybe return `0` instead of `1` make if statements for error checking way nicer
uint32_t	error_print(const char *s)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
