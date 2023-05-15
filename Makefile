# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                          :+:    :+:              #
#                                                      +:+                     #
#    By: jboeve <jboeve@student.codam.nl>             +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/17 12:05:02 by jboeve        #+#    #+#                  #
#    Updated: 2023/05/15 11:30:23 by jboeve        ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

NAME = fdf

LIBFT = libft/build/libft.a
MLX = MLX42/build/libmlx42.a


CFLAGS = -ldl -pthread -lm 
# CFLAGS += -Wall -Wextra -Werror
# CFLAGS += -g -fsanitize=address

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CFLAGS += -glfw 
endif
ifeq ($(UNAME_S),Darwin)
	CFLAGS += -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit
endif

INC = -Ilibft/include -IMLX42/include -Iinclude 

SRC_DIR = src
SRCS = main.c \
	   test.c

SRCS := $(addprefix $(SRC_DIR)/, $(SRCS))

HEADER_DIR = include
HEADERS = fdf.h
HEADERS := $(addprefix $(HEADER_DIR)/, $(HEADERS))

OBJ_DIR = obj
OBJS = $(patsubst $(SRC_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

.PHONY: make_libft

all: make_libft $(NAME)

$(NAME): $(MLX) $(OBJS) $(LIBFT) 
	$(CC) $(OBJS) $(LIBFT) $(MLX) $(CFLAGS) $(INC) -o $(NAME)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

make_libft:
	$(MAKE) -C libft

$(MLX):
	git clone https://github.com/codam-coding-college/MLX42.git
	cmake MLX42 -DCMAKE_EXPORT_COMPILE_COMMANDS=ON -B MLX42/build
	make -C MLX42/build -j4
	cp MLX42/build/compile_commands.json .

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(TEST_BIN_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean fclean all

run: all
	./$(NAME)

compile_commands: dfclean fclean
	$(MAKE) | compiledb

dfclean:
	$(MAKE) -C libft fclean
dre:
	$(MAKE) -C libft re
