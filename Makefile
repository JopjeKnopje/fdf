# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/06/27 20:32:32 by joppe         ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

######################
# OS Dependend flags #
######################
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_CFLAGS = -lglfw -lm
endif
ifeq ($(UNAME_S),Darwin)
	MLX_CFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm
	CFLAGS = -DOS_MAC
endif


RUN_CMD = ./$(NAME) maps/42-custom.fdf

CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address
# CFLAGS = -g 
# CFLAGS = -Ofast -flto -march=native


LIBFT = libft/build/libft.a
MLX = MLX42/build/libmlx42.a

INC = -Ilibft/include -IMLX42/include -Iinclude 

SRC_DIR = src
SRCS = main.c \
	   error.c \
	   utils.c \
	   fdf.c \
	   list.c \
	   free.c \
	   graphics.c \
	   line.c \
	   projector.c \
	   keyinput.c \
	   ui.c \
	   draw.c \
	   matrices.c \
	   view.c \
	   view_translations.c \
	   color.c \
	   wireframe.c \
	   text.c \
	   parser.c \
	   parser_color.c \
	   parser_utils.c \
	   math.c \
	   timer.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADER_DIR = include
HEADERS = fdf.h \
		  parser.h \
		  ui.h \
		  timer.h

HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: make_libs

all:
	$(MAKE) make_libs -j4
	$(MAKE) $(NAME) -j4

$(NAME): $(MLX) $(OBJS) $(LIBFT) 
	echo $(MLX_CFLAGS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_CFLAGS) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

make_libs: $(MLX)
	$(MAKE) -C libft
	$(MAKE) -C MLX42/build

$(MLX):
	mkdir -p MLX42/build
	cmake MLX42 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B MLX42/build
	make -C MLX42/build -j4
	cp MLX42/build/compile_commands.json .

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C MLX42/build clean
	$(MAKE) -C libft fclean
	rm -f $(NAME)

re: fclean all

run: all
	$(RUN_CMD)

compile_commands: fclean
	$(MAKE) | compiledb

norm:
	norminette libft include src

dre: re
	$(MAKE) -C libft re
