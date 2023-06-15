/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/15 20:52:19 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <math.h>


void run_tests();


int32_t	main(int32_t argc, const char *argv[])
{
	// run_tests();
	return (fdf(argc, argv));
}
