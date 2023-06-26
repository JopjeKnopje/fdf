/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ui.h                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/20 13:41:10 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/26 13:05:49 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "fdf.h"

// ui.c
void	ui_init(t_fdf *fdf);
void	ui_draw(t_fdf *fdf);
void	ui_update_texts(t_fdf *fdf);

#endif
