/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/05 16:29:47 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 15:35:44 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void		add_amb_color(t_color *color, t_scene *scene)
{
	t_vector col_vec;
	t_vector amb_vec;

	transform_color_to_vector(&scene->a_light->color, &amb_vec);
	transform_color_to_vector(color, &col_vec);
	col_vec = vector_sum(col_vec, amb_vec);
	if (scene->a_light->ratio == 0)
		vector_scale(&col_vec, 0.1);
	else
		vector_scale(&col_vec, scene->a_light->ratio);
	color_correct(&col_vec);
	color->red = (int)(col_vec.x * 255);
	color->green = (int)(col_vec.y * 255);
	color->blue = (int)(col_vec.z * 255);
}

static void	fill_zero_color(t_color *col)
{
	col->blue = 0;
	col->red = 0;
	col->green = 0;
}

static void	fill_closesst_inter(t_basic_params *b,
		t_ray_limits *ray_limits, t_objects *objs)
{
	objs->c_sp = closesst_intersection_sphere(b->point,
			b->dir, ray_limits, b->scene);
	objs->c_pl = closesst_intersection_plane(b->point,
			b->dir, ray_limits, b->scene);
	objs->c_sq = closesst_intersection_square(b->point,
			b->dir, ray_limits, b->scene);
	objs->c_tr = closesst_intersection_triangle(b->point,
			b->dir, ray_limits, b->scene);
	objs->c_cy = closesst_intersection_cylinder(b->point,
			b->dir, ray_limits, b->scene);
}

int			trace_ray(t_coordinates *orig, t_vector *dir,
		t_ray_limits *ray_limits, t_scene *scene)
{
	t_objects		objs;
	t_cl_obj_par	param;
	t_color			correct_color;
	t_basic_params	b;

	b.dir = dir;
	b.point = orig;
	b.scene = scene;
	fill_closesst_inter(&b, ray_limits, &objs);
	param = find_object(objs);
	fill_zero_color(&correct_color);
	if (param.closest_t == FLT_MAX)
		return (get_color(0, correct_color));
	if (param.obj_id == SPHERE)
		handle_obj_id_sp(&correct_color, &objs, &b, scene);
	else if (param.obj_id == PLANE)
		handle_obj_id_pl(&correct_color, &objs, &b, scene);
	else if (param.obj_id == SQUARE)
		handle_obj_id_sq(&correct_color, &objs, &b, scene);
	else if (param.obj_id == TRIANGLE)
		handle_obj_id_tr(&correct_color, &objs, &b, scene);
	else if (param.obj_id == CYLINDER)
		handle_obj_id_cy(&correct_color, &objs, &b, scene);
	return (get_color(0, correct_color));
}
