/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   ui.h                                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: jboeve <marvin@42.fr>                       +#+                      */
/*                                                  +#+                       */
/*   Created: 2023/06/20 13:41:10 by jboeve        #+#    #+#                 */
/*   Updated: 2023/06/21 00:02:15 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef UI_H
# define UI_H

# include "fdf.h"

static const char	*g_view_names[] = {
[VIEW_ORTHO] = "View: Orthographic",
[VIEW_ISO] = "View: Isometric",
[VIEW_SAVED] = "View: Saved",
};

static const char	*g_color_mode_names[] = {
[COLOR_MODE_MAP] = "Colormode: Map",
[COLOR_MODE_HEIGHT] = "Colormode: Height",
};

static const char	*g_control_text_strings[] = {
[CONTROL_TEXT_VIEWS] = "Views: 1|2|3",
[CONTROL_TEXT_SAVE_VIEW] = "Save view: Shift+3",
[CONTROL_TEXT_COLORMODE] = "Cycle colormode: G",
[CONTROL_TEXT_ROTATE_X] = "Rotate X-axis: W|S",
[CONTROL_TEXT_ROTATE_Y] = "Rotate Y-axis: Q|E",
[CONTROL_TEXT_ROTATE_Z] = "Rotate Z-axis: A|D",
[CONTROL_TEXT_MOVE_X] = "Move X-axis: left|right",
[CONTROL_TEXT_MOVE_Y] = "Move Y-axis: up|down",
};

// ui.c
void	ui_init(t_fdf *fdf);
void	ui_draw(t_fdf *fdf);
void	ui_update_texts(t_fdf *fdf);

#endif
