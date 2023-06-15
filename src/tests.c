/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   tests.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: joppe <jboeve@student.codam.nl>             +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/15 15:27:25 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/15 18:47:50 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"
#include <arpa/inet.h>
#include <stdint.h>

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



static uint32_t 	char_count(const char *s, const char c)
{
	uint32_t		i;

	i = 0;
	while (*s == ' ')
		s++;
	if (*s == '0' && (*(s + 1) == 'x' || *(s + 1) == 'X'))
		s += 2;
	while (s[i] == c)
		i++;
	return (i);
}

static uint32_t 	char_count_rev(const char *s, const char c)
{
	uint32_t		i;
	uint32_t		count = 0;

	i = ft_strlen(s) - 1;
	printf("len %d\n", i);
	while (s[i] == c)
	{
		count++;
		i--;
	}
	return (count);
}

uint32_t hex_rev(uint32_t n)
{
    return ((n >> 24) & 0xff) | ((n << 8) & 0xff0000) | ((n >> 8) & 0xff00) | ((n << 24) & 0xff000000);
}

t_rgba test_colors_linux1()
{
	// 0xff00 = 65280
	// 0x00ff = 255
	char *s = "0x0000ff";

	t_rgba c;
	const uint32_t NIBBLE = 4;
	const uint32_t pre_space = char_count(s, '0');
	const uint32_t post_space = char_count_rev(s, '0');

	printf("pre_space %d | post_space %d\n", pre_space, post_space);

	c.value = ft_atoi_hex(s);
	c.value <<= NIBBLE * pre_space;
	c.value >>= NIBBLE * post_space;
	c.value = htonl(c.value);
	c.a = 0xff;

	print_color(c);
	
	return (c);

}

typedef union s_endian_small
{
	uint32_t	value;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_endian_small;

typedef union s_endian_big
{
	uint32_t	value;
	struct
	{
		uint8_t	r;
		uint8_t	g;
		uint8_t	b;
		uint8_t	a;
	};
}	t_endian_big;


void print_union(uint32_t value)
{
	int i = 0;
	while (i < 4)
	{
		printf("%x %x\n", i, value << 8 * i);
		i++;
	}

}


/*

	0xaabbccdd
	  r g b a
	0xaabbccdd
	  a b g r

*/

void test_unions()
{
	t_endian_big big;
	t_endian_small small;

	const char *s = "0xaabbccdd";

	big.value = ft_atoi_hex(s);
	small.value = ft_atoi_hex(s);

	print_union(big.value);
	print_union(small.value);
	printf("%x\n", big.a);
	printf("%x\n", small.a);
}

void run_tests()
{
#ifdef OS_MAC
	test_colors_mac();
#else
	// test_colors_linux();
	test_colors_linux1();
#endif
}
