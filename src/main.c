/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/19 23:40:18 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void test(const char *s)
{
	uint32_t a = strtol(s, NULL, 16);
	uint32_t b = ft_atoi_hex(s);
	if (a != b)
		printf("input [%s] failed a: %d b: %d\n", s, a, b);
}

int32_t	main(int32_t argc, const char *argv[])
{
	const char *input[] = {
 		"0xaaaa",
 		"0x aaa",
 		"0xaa aa",
 		"xaaaa",
 		"x aaa",
 		"xaa aa",
 		"aaaa",
 		" aaa",
 		"aa aa",
 		"0xf1 3",
 		"0xf123",
 		"0xffff",
 		"xf1 3",
 		"xf123",
 		"xffff",
 		"f1 3",
 		"f123",
 		"ffff",
		" x",
		"f ",
		" 0",
		"1",
		NULL
	};
	for (int i = 0; input[i]; i++)
	{
		test(input[i]);
	}

	// return (fdf(argc, argv));
}
