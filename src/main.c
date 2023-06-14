/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   main.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/05/15 11:33:08 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/14 19:01:27 by jboeve        ########   odam.nl         */
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



int32_t	main(int32_t argc, const char *argv[])
{
	// const char *inputs[] = {
	// 	"0,0x30fc03FF",
	// 	"123,0xff",
	// 	"0,0xff00",
	// 	"0,0xff00ffff",
	// 	"0,0xff00ff",
	// 	"0,0x000000ff",
	// 	"0,0x00aa00ff",
	// 	0,
	// };
	//
	// const char *outputs[] = {
	// 	"0x30fc03FF",
	// 	"0xff0000ff",
	// 	"0xff0000ff",
	// 	"0xff00ffff",
	// 	"0xff00ffff",
	// 	"0x000000ff",
	// 	"0x00aa00ff",
	// 	"0x00aa00ff",
	// 	0,
	// };
	//
	// int i = 0;
	// while (inputs[i])
	// {
	// 	t_rgba c = parse_color(inputs[i]);
	// 	uint32_t expected = ft_atoi_hex(outputs[i]);
	// 	if (expected != c.value)
	// 		printf("FAILED \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
	// 	else
	// 		printf("passed \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
	// 	i++;
	// }
	// t_rgba c;

	return (fdf(argc, argv));
}
