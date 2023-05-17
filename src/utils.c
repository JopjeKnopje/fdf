/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   utils.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/05/17 17:11:15 by joppe         #+#    #+#                 */
/*   Updated: 2023/05/17 17:23:08 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

uint32_t ft_atoi_hex(const char *s)
{
	int	i;
	int	num;
	int	sign;

	num = 0;
	sign = 0;
	i = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while ((s[i] == '-' || s[i] == '+') && !sign)
	{
		if (s[i] == '-')
			sign = -1;
		if (s[i] == '+')
			sign = 1;
		i++;
	}
	if (!sign)
		sign = 1;
	while (s[i])
	{
		if (ft_isdigit(s[i]))
			num = num * 16 + s[i] - '0';
		else if (s[i] >= 'a' && s[i] <= 'f')
			num = num * 16 + s[i] - ('x' - 'a');
		i++;
	}
	return (num * sign);
}
