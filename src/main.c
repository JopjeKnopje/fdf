/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/17 09:07:57 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"


int32_t main(int32_t argc, const char* argv[])
{
	t_fdf fdf;
	if (argc != 2)
		return (error_message(ERR_ARGS_INVALID));
	parser(argv[1]);
}
