/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/05/17 09:46:46 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>


int32_t main1(int32_t argc, const char* argv[])
{
	t_fdf fdf;
	if (argc != 2)
		return (error_message(ERR_ARGS_INVALID));
	parser(argv[1]);
}

uint8_t check_extension(const char *map, const char *ext);

int32_t main(int32_t argc, const char* argv[])
{
	const char *maps[] = 
	{
		".fdf",
		"a.fdf",
		"a.fdf ",
		"a.faf",
		"adsada.faf",
		".faf",
	};
	const int output[] = 
	{
		0,
		1,
		0,
		0,
		0,
		0,
	};

	int i = 0;
	while (maps[i]) 
	{
		if (check_extension(maps[i], ".fdf") == output[i])
		{
			printf("passed\n");
		}
		else {
			printf("failed\n");
		}
		i++;
	}
}
