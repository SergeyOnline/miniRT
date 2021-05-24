/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 18:44:11 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 18:52:52 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# include "structures.h"
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>
# include "mlx.h"
# include <math.h>
# include <float.h>
# define SPHERE 1
# define SQUARE 2
# define PLANE 3
# define CYLINDER 4
# define TRIANGLE 5
# define BMP_FILE_HEADER 14
# define BMP_INFO_HEADER 40
# define BMP_NAME "new_image.bmp"

void			*ft_memset(void *b, int c, int len);
int				ft_strncmp(const char *str1, const char *str2, int n);
char			*ft_strdup(const char *s1);
char			*ft_strjoin(char const *s1, char const *s2);
char			*ft_strrchr(const char *str, int c);
char			*ft_strchr(const char *str, int c);
int				get_next_line(int fd, char **line);
int				*ft_data_parser(t_scene *scene, char *name);
void			*ft_memcpy(void *dst, const void *src, size_t n);
void			*ft_calloc(size_t count, size_t size);
char			**ft_split(char const *s, char c);
int				ft_atoi(const char *str);
float			ft_atof(const char *str);
int				ft_digits_in_number(int num);
void			clear_two_dim_arr(char **arr);
void			ft_fill_null_scene(t_scene *scene);
void			ft_clear_scene(t_scene *scene);
void			ft_putstr(char *s);
int				ft_is_all_digit(char *str);
int				ft_is_float(char *str);
int				ft_strlen(const char *s);
void			transform_color_to_vector(t_color *color, t_vector *col_vec);
int				get_color(int t, t_color color);
void			color_correct(t_vector *color);
float			deg_to_rad(float deg);
t_cam_ring		*new_cam_ring(t_camera cam);
void			add_element_cam_ring(t_cam_ring **ring, t_camera cam);
void			remove_element_cam_ring(t_cam_ring **ring);
void			clear_cam_ring(t_cam_ring **ring);
t_sp_ring		*new_sp_ring(t_sphere sp);
void			add_element_sp_ring(t_sp_ring **ring, t_sphere sp);
void			remove_element_sp_ring(t_sp_ring **ring);
void			clear_sp_ring(t_sp_ring **ring);
t_pl_ring		*new_pl_ring(t_plane pl);
void			add_element_pl_ring(t_pl_ring **ring, t_plane pl);
void			remove_element_pl_ring(t_pl_ring **ring);
void			clear_pl_ring(t_pl_ring **ring);
t_sq_ring		*new_sq_ring(t_square sq);
void			add_element_sq_ring(t_sq_ring **ring, t_square sq);
void			remove_element_sq_ring(t_sq_ring **ring);
void			clear_sq_ring(t_sq_ring **ring);
t_cy_ring		*new_cy_ring(t_cylinder cy);
void			add_element_cy_ring(t_cy_ring **ring, t_cylinder cy);
void			remove_element_cy_ring(t_cy_ring **ring);
void			clear_cy_ring(t_cy_ring **ring);
t_tr_ring		*new_tr_ring(t_triangle tr);
void			add_element_tr_ring(t_tr_ring **ring, t_triangle tr);
void			remove_element_tr_ring(t_tr_ring **ring);
void			clear_tr_ring(t_tr_ring **ring);
t_light_ring	*new_light_ring(t_light light);
void			add_element_light_ring(t_light_ring **ring, t_light light);
void			remove_element_light_ring(t_light_ring **ring);
void			clear_light_ring(t_light_ring **ring);
int				check_color_err(char *color);
int				check_vector_err(char *vector);
int				check_coord_err(char *coord);
int				handle_resolution(t_scene *scene, char **data);
int				handle_a_lightning(t_scene *scene, char **data);
int				handle_cam(t_scene *scene, char **data);
int				handle_light(t_scene *scene, char **data);
int				handle_plane(t_scene *scene, char **data);
int				handle_square(t_scene *scene, char **data);
int				handle_sphere(t_scene *scene, char **data);
int				handle_cylinder(t_scene *scene, char **data);
int				handle_triangle(t_scene *scene, char **data);
t_vector		canvas_to_viewport(float x, float y, t_scene *scene);
t_solv_quad		intersect_ray_sphere(t_vector *orig,
	t_vector *dir, t_sphere *sp);
t_cl_obj_par	find_object(t_objects objects);
void			find_cy(t_cl_obj_par *param, t_objects *objects);
void			find_sp(t_cl_obj_par *param, t_objects *objects);
void			find_sq(t_cl_obj_par *param, t_objects *objects);
void			find_pl(t_cl_obj_par *param, t_objects *objects);
void			find_tr(t_cl_obj_par *param, t_objects *objects);
void			add_amb_color(t_color *color, t_scene *scene);
t_color			compute_lightning(t_basic_params *base,
		t_vector normal, t_color color);
t_closest_sp	closesst_intersection_sphere(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene);
int				trace_ray(t_coordinates *orig, t_vector *dir,
		t_ray_limits *ray_limits, t_scene *scene);
void			handle_obj_id_sp(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene);
void			handle_obj_id_pl(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene);
void			handle_obj_id_sq(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene);
void			handle_obj_id_tr(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene);
void			handle_obj_id_cy(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene);
t_closest_pl	closesst_intersection_plane(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene);
t_closest_sq	closesst_intersection_square(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene);
t_closest_tr	closesst_intersection_triangle(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene);
t_closest_cy	closesst_intersection_cylinder(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene);
float			intersection_disc(t_coordinates *point,
	t_vector *dir, t_ray_limits *r_lim, t_disc *disc);
t_tmp_params_cy	find_cy_wall_points(t_basic_params *b_par,
		t_cylinder *cy, t_closest_cy *result);
t_color			get_sphere_color(t_closest_sp c_sp,
		t_basic_params *b, t_color correct_color);
t_color			get_plane_color(t_closest_pl c_pl,
		t_basic_params *b, t_color correct_color);
t_color			get_square_color(t_closest_sq c_sq,
		t_basic_params *b, t_color correct_color);
t_color			get_triangle_color(t_closest_tr c_tr,
		t_basic_params *b, t_color correct_color);
t_color			get_cylinder_color(t_closest_cy c_cy,
		t_basic_params *b, t_color correct_color);
void			fill_result(t_closest_cy *result,
		t_cylinder *cy, float t_closesst);
void			vector_fill(t_vector *v, float x, float y, float z);
void			vector_normalaze(t_vector *vect);
float			vector_len(t_vector *v);
t_vector		vector_substract(t_vector v1, t_vector v2);
t_vector		vector_sum(t_vector v1, t_vector v2);
float			vector_dot(t_vector v1, t_vector v2);
void			vector_scale(t_vector *v, float factor);
t_vector		vector_cross(t_vector *v1, t_vector *v2);
void			zero_matrix44(t_matrix44 *matrix);
t_matrix44		mult_matrix(t_matrix44 *m1, t_matrix44 *m2);
t_matrix44		transposed_matrix(t_matrix44 *matrix);
t_coordinates	mult_coord_matrix(t_coordinates coord, t_matrix44 matrix);
t_vector		mult_dir_matrix(t_vector vec, t_matrix44 matrix);
t_matrix44		inverse_matrix(t_matrix44 *matrix);
void			save_image(t_scene *scene, char *name, t_mlx *mlx);
void			render(t_mlx *new_mlx, t_scene *scene);
int				close_window(void);

#endif
