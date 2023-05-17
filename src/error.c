/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                           :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 21:17:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/17 15:56:05 by jboeve        ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t	error_message(t_error err)
{
	return (error_print(ERROR_NAME[err]));
}

uint32_t	error_print(const char *s)
{
	write(STDERR_FILENO, "Error: ", ft_strlen("Error: "));
	write(STDERR_FILENO, s, ft_strlen(s));
	write(STDERR_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
