/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/17 17:21:49 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

int32_t	main(int32_t argc, const char *argv[])
{
	const char *s = "ff123";
	uint32_t a = strtol(s, NULL, 16);
	uint32_t b = ft_atoi_hex(s);
	printf("a %d\n", a);
	printf("b %d\n", b);

	// return (fdf(argc, argv));
}
