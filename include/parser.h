/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parser.h                                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/20 13:25:58 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/26 16:59:40 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */
#ifndef PARSER_H
# define PARSER_H

# include "fdf.h"

// parser_utils.c
uint8_t			parser_util_open_map(const char *map);
void			parser_util_add_point(t_fdf *fdf, t_point point);
const char		*parser_map_name(const char *map);

// parser_color.c
t_rgba			parse_color(const char *s);

#endif
