# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/15 19:27:35 by sbroderi          #+#    #+#              #
#    Updated: 2020/10/15 19:27:38 by sbroderi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = miniRT

SRC_DIR = ./srcs/

INCLUDES = -I./includes/ -I.$(LIB_DIR)

LIST = main.c \
	canvas_to_viewport.c \
	check_color_err.c \
	check_coord_err.c \
	check_vector_err.c \
	close_window.c \
	closesst_intersection_cylinder.c \
	closesst_intersection_plane.c \
	closesst_intersection_sphere.c \
	closesst_intersection_square.c \
	closesst_intersection_triangle.c \
	color_operations.c \
	compute_lightning.c \
	deg_to_rad.c \
	find_cy_wall_points.c \
	find_object_help.c \
	find_object.c \
	ft_atof.c \
	ft_atoi.c \
	ft_calloc.c \
	ft_clear_scene.c \
	ft_clear_two_dim_arr.c \
	ft_data_parser.c \
	ft_digits_in_number.c \
	ft_fill_null_scene.c \
	ft_get_next_line.c \
	ft_is_all_digit.c \
	ft_is_float.c \
	ft_memcpy.c \
	ft_memset.c \
	ft_putstr.c \
	ft_split.c \
	ft_strrchr.c \
	ft_strchr.c \
	ft_strdup.c \
	ft_strjoin.c \
	ft_strlen.c \
	ft_strncmp.c \
	get_color.c \
	get_obj_color.c \
	handle_a_lightning.c \
	handle_cam.c \
	handle_cylinder.c \
	handle_light.c \
	handle_plane.c \
	handle_resolution.c \
	handle_sphere.c \
	handle_square.c \
	handle_triangle.c \
	intersect_ray_sphere.c \
	matrix_oper.c \
	matrix_zero.c \
	render.c \
	ring_cam.c \
	ring_cy.c \
	ring_light.c \
	ring_pl.c \
	ring_sp.c \
	ring_sq.c \
	ring_tr.c \
	save_image.c \
	trace_ray_help.c \
	trace_ray.c \
	vector_fill.c \
	vector_len.c \
	vector_normalaze.c \
	vector_oper.c
SRC = $(addprefix $(SRC_DIR), $(LIST))
OBJ = $(patsubst %.c,%.o,$(SRC))

LIB_DIR = ./minilibx_mms/

FLAGS = -Wall -Wextra -Werror -O3

MLFLAGS = -L. -lmlx -framework OpenGL -framework AppKit

.PHONY: all, clean, clean, re, bonus, lmlx

all: lmlx $(NAME)

$(NAME): $(OBJ)

	gcc $(MLFLAGS) $(OBJ) $(LIB) $(INCLUDES) -o $(NAME)

lmlx:
	@$(MAKE) -C $(LIB_DIR) --silent
	@cp ./minilibx_mms/libmlx.dylib .

%.o: %.c ./includes/minirt.h ./includes/structures.h
	@gcc $(FLAGS) $(INCLUDES) -c $< -o $@

bonus: all

clean:
	@rm -f $(OBJ)

fclean: clean
	
	@rm -f $(NAME)
	@rm -f libmlx.dylib

re: clean all