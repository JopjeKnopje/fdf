/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fdf.h                                             :+:    :+:             */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/04/23 01:09:59 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/25 23:43:41 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "libft.h"
# include "timer.h"
# include <MLX42/MLX42.h>
# include <stdint.h>
# include <stdlib.h>
# include <unistd.h>

# define COLOR_BACKGROUND_UI 0x44444466
# define COLOR_BACKGROUND 0x333333ff
# define COLOR_POINT_DEFAULT 0xCCCCCCFF

# define AMPLITUDE_STEP 0.01f
# define ANGLE_STEP 0.025f
# define SCALAR_STEP 0.1f
# define SCALAR_MAX 10000.0f

# define FONT_HEIGHT 20
# define NIBBLE 4

typedef union s_rgba
{
	uint32_t	value;
	struct
	{
		uint8_t	a;
		uint8_t	b;
		uint8_t	g;
		uint8_t	r;
	};
}	t_rgba;

// Very cursed.
typedef enum e_dimensions {
	DIM_WINDOW_WIDTH = 1024,
	DIM_WINDOW_HEIGHT = 720,
	DIM_UI_WIDTH = 280,
	DIM_UI_HEIGHT = DIM_WINDOW_HEIGHT,
	DIM_VIEWPORT_WIDTH = DIM_WINDOW_WIDTH,
	DIM_VIEWPORT_HEIGHT = DIM_WINDOW_HEIGHT,
}	t_dimensions;

typedef enum e_color_mode {
	COLOR_MODE_MAP,
	COLOR_MODE_HEIGHT,
	COLOR_MODE_COUNT,
}	t_color_mode;

typedef union s_color_gradient
{
	t_rgba	c[2];
	struct
	{
		t_rgba	c1;
		t_rgba	c2;
	};
}	t_color_gradient;

typedef struct s_mat3x3
{
	float	data[3][3];
}	t_mat3x3;

typedef struct s_point
{
	float		x;
	float		y;
	float		z;
	int32_t		actual_z;
	t_rgba		color;
}	t_point;

typedef struct s_vec3
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
}	t_vec3;

typedef struct s_vec2
{
	int32_t		x;
	int32_t		y;
	int32_t		z;
}	t_vec2;

typedef struct s_color_info {
	float				end_z;
	float				start_z;
	int32_t				len;
	uint32_t			step;
	t_color_gradient	g;
}	t_color_info;

typedef struct s_bresenham
{
	t_vec3			start;
	t_vec3			end;
	t_vec2			delta;
	t_vec2			direction;
	int32_t			err;
	t_color_info	info;
}	t_bresenham;

typedef struct s_node
{
	t_point			point;
	struct s_node	*next;
}	t_node;

typedef struct s_map
{
	t_node		*points_list;
	t_node		*points_last;
	t_point		*points;
	const char	*name;
	int32_t		min_z;
	int32_t		max_z;
	uint32_t	width;
	uint32_t	height;
}	t_map;

typedef enum e_views {
	VIEW_ORTHO,
	VIEW_ISO,
	VIEW_SAVED,
}	t_views;

typedef struct s_view
{
	t_mat3x3		id_matrix;
	int32_t			x_move;
	int32_t			y_move;
	float			scalar;
	float			amplitude;
	t_color_mode	color_mode;
}	t_view;

typedef struct s_projector
{
	t_view	active_view;
	t_view	saved_view;
}	t_projector;

typedef enum e_texts {
	TEXT_FPS,
	TEXT_VIEW,
	TEXT_COLOR_MODE,
	TEXT_SCALAR,
	TEXT_AMPLITUDE,
	TEXT_MAP_WIDTH,
	TEXT_MAP_HEIGHT,
	TEXT_COUNT,
}	t_texts;

typedef enum e_control_texts {
	CONTROL_TEXT_VIEWS,
	CONTROL_TEXT_SAVE_VIEW,
	CONTROL_TEXT_COLORMODE,
	CONTROL_TEXT_ROTATE_X,
	CONTROL_TEXT_ROTATE_Y,
	CONTROL_TEXT_ROTATE_Z,
	CONTROL_TEXT_MOVE_X,
	CONTROL_TEXT_MOVE_Y,
	CONTROL_TEXT_COUNT,
}	t_control_texts;

typedef struct s_text_image {
	mlx_image_t	*image;
	uint32_t	x;
	uint32_t	y;
	char		*s;
	bool		redraw;
}	t_text_image;

typedef struct s_ui
{
	mlx_image_t		*image;
	t_text_image	texts[TEXT_COUNT + CONTROL_TEXT_COUNT];
	bool			key_states[MLX_KEY_MENU - MLX_KEY_SPACE];
	uint32_t		fps;
}	t_ui;

typedef struct s_fdf
{
	mlx_t		*mlx;
	t_map		*map;
	t_timer		*fps_timer;
	mlx_image_t	*image;
	t_projector	projector;
	t_ui		ui;
}	t_fdf;

typedef enum e_direction {
	DIR_NEGATIVE = -1,
	DIR_POSTIVE = 1,
}	t_direction;

typedef enum e_rotate_axis
{
	AXIS_X,
	AXIS_Y,
	AXIS_Z,
	AXIS_COUNT,
}	t_axis;

typedef enum e_error
{
	ERR_ARGS_INVALID,
	ERR_MAP_INVALID,
	ERR_MALLOC_FAILURE,
	ERR_COUNT,
}	t_error;

// fdf.c
int32_t			fdf(int32_t argc, const char *argv[]);

// parser.c
uint32_t		parser(t_fdf *fdf, const char *map);

// utils.c
uint8_t			check_extension(const char *map, const char *ext);
uint32_t		list_to_arr(t_fdf *fdf);
t_mat3x3		mat3x3mul(t_mat3x3 m1, t_mat3x3 m2);
t_point			mat1x3mul(t_point point, t_mat3x3 m);
uint8_t			points_in_window(mlx_image_t *image, t_point p1, t_point p2);

// list.c
int				lstsize(t_node *lst);
t_node			*lstadd_back(t_node **lst, t_node *new);
t_node			*lstlast(t_node *lst);
t_node			*lstnew(t_point point);

// free.c
void			free_split(char **s_split);
void			free_lst(t_node *lst);
void			free_fdf(t_fdf *fdf);

// graphics.c
int32_t			graphics_init(t_fdf *fdf);

// line.c
void			line_draw(t_fdf *fdf, t_point p_start, t_point p_end);

// keyinput.c
void			key_hook(void *param);

// error.c
uint32_t		error_message(t_error err);
uint32_t		error_print(const char *s);

// projector.c
void			projector_init(t_fdf *fdf);
t_point			projector(t_fdf *fdf, t_point point);

// draw.c
void			draw_hook(void *param);
void			fdf_put_pixel(t_fdf *fdf, t_vec3 *p, uint32_t c);

// matrices.c
t_mat3x3		get_matrix_rotate_x(float angle);
t_mat3x3		get_matrix_rotate_y(float angle);
t_mat3x3		get_matrix_rotate_z(float angle);
t_mat3x3		get_matrix_ortho(void);
t_mat3x3		get_matrix_iso(void);

// view.c
void			view_cylce_color_mode(t_fdf *fdf, t_direction dir);
void			view_select(t_fdf *fdf, t_views view);
void			view_save(t_projector *p);

// view_translations.c
void			view_scale(t_fdf *fdf, t_view *view, t_direction dir);
void			view_amplitude(t_fdf *fdf, t_view *view, t_direction dir);
void			view_move(t_view *view, t_axis axis, t_direction dir);
void			view_rotate(t_view *view, t_axis axis, t_direction dir);

// rotate.c
void			rotate(t_fdf *fdf, t_axis axis, t_direction dir);

// color.c
t_rgba			get_color(t_fdf *fdf, t_color_info *info);

// wireframe.c
void			wireframe_draw(t_fdf *fdf);

// text.c
void			text_set_num(t_text_image *text, const char *s_base, int32_t n);
void			text_set(t_text_image *text, char *s);
void			text_draw(mlx_t *mlx, t_text_image *text);

// math.c
int32_t			ft_abs(int32_t n);

// meuk.c
void			print_text(t_text_image *t);
void			print_point(t_point point);
void			mat_print(t_mat3x3 m);
void			print_points(t_fdf *fdf);
void			print_points_arr(t_fdf *fdf);
void			print_color(t_rgba c);

#endif
