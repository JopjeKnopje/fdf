/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/16 21:17:21 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/16 21:26:48 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

const static char *ERROR_NAME[] = {
	"Usage: ./fdf <map>",
};

uint32_t error_message(t_error err)
{
	write(STDOUT_FILENO, ERROR_NAME[err], ft_strlen(ERROR_NAME[err]));
	write(STDOUT_FILENO, "\n", 1);
	return (EXIT_FAILURE);
}
