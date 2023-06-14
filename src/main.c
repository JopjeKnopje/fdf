/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                             :+:    :+:            */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/14 10:26:16 by joppe         ########   odam.nl         */
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


t_rgba	parse_color(const char *s);

int32_t	main(int32_t argc, const char *argv[])
{


	// 0xFF -> 0xFF0000FF
	// 0xFF00 -> 0xFF0000FF
	// 0xFF00FF -> 0xFF00FFFF
	const char *inputs[] = {
		"123,0xff",
		"0,0xff00",
		"0,0xff00ff",
		0,
	};

	const char *outputs[] = {
		"0xff0000ff",
		"0xff0000ff",
		"0xff00ffff",
		0,
	};

	int i = 0;
	while (inputs[i])
	{
		t_rgba c = parse_color(inputs[i]);
		printf("[%s] \t-> \t[%x]\n", inputs[i], c.value);	
		i++;
	}



	// return (fdf(argc, argv));
}
