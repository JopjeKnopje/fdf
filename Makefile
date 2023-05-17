# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/05/17 11:36:24 by jboeve        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = libft/build/libft.a
MLX = MLX42/build/libmlx42.a


# CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	MLX_CFLAGS = -lglfw 
endif
ifeq ($(UNAME_S),Darwin)
	MLX_CFLAGS = -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -ldl -pthread -lm
endif

INC = -Ilibft/include -IMLX42/include -Iinclude 

SRC_DIR = src
SRCS = main.c \
	   parser.c \
	   error.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADER_DIR = include
HEADERS = fdf.h
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: make_libft

all: make_libft $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT) 
	echo $(MLX_CFLAGS)
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(MLX_CFLAGS) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $< 

make_libft:
	$(MAKE) -C libft

MLX42:
	git clone https://github.com/codam-coding-college/MLX42.git

$(MLX): MLX42
	cmake MLX42 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B MLX42/build
	make -C MLX42/build -j4
	cp MLX42/build/compile_commands.json .

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_BIN_DIR)
	$(MAKE) -C MLX42/build clean

fclean: clean
	rm -f $(NAME)
	$(MAKE) -C libft fclean

re: fclean all
	$(MAKE) -C libft re


run: all
	# open -a terminal ./fdf
	./$(NAME) maps/elem-col.fdf

compile_commands: dfclean fclean
	$(MAKE) | compiledb
