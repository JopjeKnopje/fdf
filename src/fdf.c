/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/17 14:34:42 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/20 02:17:32 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int32_t	fdf(int32_t argc, const char *argv[])
{
	t_fdf	fdf;
	ft_bzero(&fdf, sizeof(t_fdf));

	if (argc != 2)
		return (error_message(ERR_ARGS_INVALID));
	if (parser(&fdf, argv[1]))
		return (1);
	if (graphics_init(&fdf))
		return (1);
	free_lst(fdf.points);
	return (0);
}
