/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   tests.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/15 15:27:25 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/15 15:30:02 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_rgba	parse_color(const char *s);

void test_colors_mac()
{
	const char *inputs[] = {
		"123,0xff",
		"0,0xff00",
		"0,0xff00ffff",
		"0,0xff00ff",
		"0,0x000000ff",
		"0,0x00aa00ff",
		0,
	};

	const char *outputs[] = {
		"0xff0000ff",
		"0xff0000ff",
		"0xff00ffff",
		"0xff00ffff",
		"0x000000ff",
		"0x00aa00ff",
		0,
	};

	int i = 0;
	while (inputs[i])
	{
		t_rgba c = parse_color(inputs[i]);
		uint32_t expected = ft_atoi_hex(outputs[i]);
		if (expected != c.value)
			printf("FAILED \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
		else
			printf("passed \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
		i++;
	}
}

void test_colors_linux()
{
	const char *inputs[] = {
		"123,0xff",
		"0,0xff00",
		"0,0xff00ffff",
		"0,0xff00ff",
		"0,0x000000ff",
		"0,0x00aa00ff",
		0,
	};

	const char *outputs[] = {
		"0xff0000ff",
		"0xff0000ff",
		"0xffff00ff",
		"0xffff00ff",
		"0xff000000",
		"0xff00aa00",
		0,
	};

	int i = 0;
	while (inputs[i])
	{
		t_rgba c = parse_color(inputs[i]);
		uint32_t expected = ft_atoi_hex(outputs[i]);
		if (expected != c.value)
			printf("FAILED \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
		else
			printf("passed \t[%d] | input [%s] | expected: %x | result: %x\n", i, inputs[i], expected, c.value);
		i++;
	}
}

void run_tests()
{
#ifdef OS_MAC
	test_colors_mac();
#else
	test_colors_linux();
#endif
}
