/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structures.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 14:30:10 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 18:43:18 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURES_H
# define STRUCTURES_H

typedef struct				s_quad_coeffs
{
	float					k1;
	float					k2;
	float					k3;
	float					discr;
}							t_quad_coeffs;

typedef struct				s_matrix44
{
	float					m[4][4];
}							t_matrix44;

typedef struct				s_ray_limits
{
	float					t_min;
	float					t_max;
}							t_ray_limits;

typedef struct				s_color
{
	int						red;
	int						green;
	int						blue;
}							t_color;

typedef struct				s_coordinates
{
	float					x;
	float					y;
	float					z;
}							t_coordinates;

typedef t_coordinates		t_vector;

typedef struct				s_tr_coeffs
{
	float					a;
	float					b;
	float					c;
	float					det;
	t_vector				v1;
	t_vector				v2;
}							t_tr_coeffs;

typedef struct				s_resolution
{
	int						height;
	int						width;
}							t_resolution;

typedef struct				s_solv_quad
{
	float					t1;
	float					t2;
}							t_solv_quad;

typedef struct				s_a_lightning
{
	float					ratio;
	t_color					color;
}							t_a_lightning;

typedef struct				s_camera
{
	t_coordinates			coord;
	t_vector				vector;
	float					fov;
}							t_camera;

typedef struct				s_light
{
	t_coordinates			coord;
	float					b_ratio;
	t_color					color;
}							t_light;

typedef struct				s_sphere
{
	t_coordinates			center;
	float					diameter;
	t_color					color;
}							t_sphere;

typedef struct				s_plane
{
	t_coordinates			coord;
	t_vector				vector;
	t_color					color;
}							t_plane;

typedef struct				s_square
{
	t_coordinates			coord;
	t_vector				vector;
	float					side;
	t_color					color;
}							t_square;

typedef struct				s_disk
{
	t_coordinates			center;
	t_vector				vector;
	float					diameter;
	t_color					color;
}							t_disc;

typedef struct				s_cylinder
{
	t_coordinates			coord;
	t_vector				vector;
	float					diameter;
	float					height;
	t_color					color;
	t_disc					up_disc;
	t_disc					down_disc;
}							t_cylinder;

typedef struct				s_triangle
{
	t_coordinates			first;
	t_coordinates			second;
	t_coordinates			third;
	t_color					color;
}							t_triangle;

typedef struct				s_cam_ring
{
	int						size;
	t_camera				cam;
	struct s_cam_ring		*next;
	struct s_cam_ring		*prev;
}							t_cam_ring;

typedef struct				s_sp_ring
{
	int						size;
	t_sphere				sp;
	struct s_sp_ring		*next;
	struct s_sp_ring		*prev;
}							t_sp_ring;

typedef struct				s_pl_ring
{
	int						size;
	t_plane					pl;
	struct s_pl_ring		*next;
	struct s_pl_ring		*prev;
}							t_pl_ring;

typedef struct				s_sq_ring
{
	int						size;
	t_square				sq;
	struct s_sq_ring		*next;
	struct s_sq_ring		*prev;
}							t_sq_ring;

typedef struct				s_cy_ring
{
	int						size;
	t_cylinder				cy;
	struct s_cy_ring		*next;
	struct s_cy_ring		*prev;
}							t_cy_ring;

typedef struct				s_tr_ring
{
	int						size;
	t_triangle				tr;
	struct s_tr_ring		*next;
	struct s_tr_ring		*prev;
}							t_tr_ring;

typedef struct				s_light_ring
{
	int						size;
	t_light					light;
	struct s_light_ring		*next;
	struct s_light_ring		*prev;
}							t_light_ring;

typedef struct				s_scene
{
	t_resolution			*res;
	t_a_lightning			*a_light;
	t_cam_ring				*cam_ring;
	t_light_ring			*light_ring;
	t_sp_ring				*sp_ring;
	t_pl_ring				*pl_ring;
	t_sq_ring				*sq_ring;
	t_cy_ring				*cy_ring;
	t_tr_ring				*tr_ring;
	int						save;
}							t_scene;

typedef struct				s_closest_sp
{
	t_sphere				*sp;
	float					t_closest;
}							t_closest_sp;

typedef struct				s_closest_pl
{
	t_plane					*pl;
	float					t_closest;
}							t_closest_pl;

typedef struct				s_closest_sq
{
	t_square				*sq;
	float					t_closest;
}							t_closest_sq;

typedef struct				s_closest_tr
{
	t_triangle				*tr;
	float					t_closest;
}							t_closest_tr;

typedef struct				s_closest_cy
{
	t_cylinder				*cy;
	float					t_closest;
}							t_closest_cy;

typedef struct				s_tmp_params_cy
{
	t_solv_quad				solve_quad;
	float					closest_t;
	int						err_code;
	t_vector				inter_cy;
}							t_tmp_params_cy;

typedef struct				s_tmp_params_dick
{
	float					a;
	float					b;
	float					d2;
	t_vector				p;
	t_vector				v;
}							t_tmp_params_dick;

typedef struct				s_tmp_cross_param
{
	t_vector				cross;
	t_vector				cross2;
	t_vector				norm;
}							t_tmp_cross_param;

typedef struct				s_tmp_norm_param
{
	t_vector				norm;
	t_vector				norm_up;
	t_vector				norm_down;
}							t_tmp_norm_param;

typedef struct				s_cl_obj_par
{
	int						obj_id;
	float					closest_t;
	t_color					color;
}							t_cl_obj_par;

typedef struct				s_objects
{
	t_closest_sq			c_sq;
	t_closest_pl			c_pl;
	t_closest_sp			c_sp;
	t_closest_tr			c_tr;
	t_closest_cy			c_cy;
}							t_objects;

typedef struct				s_params_light_calc
{
	t_coordinates			*point;
	t_vector				*normal;
	t_vector				*dir;
	t_ray_limits			*r_lim;
}							t_params_light_calc;

typedef struct				s_basic_params
{
	t_coordinates			*point;
	t_vector				*dir;
	t_scene					*scene;
	t_ray_limits			*r_lim;
}							t_basic_params;

typedef struct				s_img
{
	void					*img;
	char					*addr;
	int						bits_per_pixel;
	int						size_line;
	int						endian;
}							t_img;

typedef struct				s_mlx
{
	void					*mlx;
	void					*window;
	t_img					*img;
}							t_mlx;

typedef struct				s_change_cam
{
	t_scene					*scene;
	t_mlx					*new_mlx;
}							t_change_cam;

#endif
