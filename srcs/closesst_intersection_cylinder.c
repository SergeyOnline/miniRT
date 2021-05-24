/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closesst_intersection_cylinder.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:09:39 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 11:46:40 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

float					intersection_disc(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_disc *disc)
{
	float				result;
	float				t_closest;
	t_tmp_params_dick	params;
	t_vector			tmp;

	result = r_lim->t_max;
	params.a = vector_dot(vector_substract(*point, disc->center), disc->vector);
	params.b = vector_dot(*dir, disc->vector);
	if (params.b == 0 || (params.a < 0 && params.b < 0) ||
		(params.a > 0 && params.b > 0))
		return (result);
	t_closest = -params.a / params.b;
	if (t_closest < 0 || result < t_closest)
		return (result);
	tmp = *dir;
	vector_scale(&tmp, t_closest);
	params.p = vector_sum(*point, tmp);
	params.v = vector_substract(params.p, disc->center);
	params.d2 = vector_dot(params.v, params.v);
	if (sqrt(params.d2) <= disc->diameter / 2)
	{
		result = t_closest;
		return (result);
	}
	return (result);
}

static int				cylinder_wall(t_tmp_params_cy *tmp_params,
		t_vector *cy_vector, t_closest_cy *result, t_cylinder *cy)
{
	float		a;
	float		b;
	t_plane		plane;
	float		plane_t;

	plane.coord = cy->coord;
	plane.vector = cy->vector;
	a = vector_dot(vector_substract(tmp_params->inter_cy, plane.coord),
		plane.vector);
	b = vector_dot(*cy_vector, plane.vector);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (1);
	plane_t = -a / b;
	if (plane_t < 0 && result->t_closest < plane_t)
		fill_result(result, NULL, FLT_MAX);
	if (plane_t <= cy->height / 2)
		fill_result(result, cy, tmp_params->closest_t);
	else
		fill_result(result, NULL, FLT_MAX);
	return (0);
}

static int				cl_disc(t_coordinates *point,
		t_vector *dir, t_closest_cy *result, t_cylinder *cy)
{
	float			cl_d;
	t_ray_limits	r_lim;

	r_lim.t_max = FLT_MAX;
	cl_d = intersection_disc(point, dir, &r_lim, &cy->down_disc);
	if (cl_d != FLT_MAX && cl_d < result->t_closest)
		fill_result(result, cy, cl_d);
	cl_d = intersection_disc(point, dir, &r_lim, &cy->up_disc);
	if (cl_d != FLT_MAX && cl_d < result->t_closest)
		fill_result(result, cy, cl_d);
	return (0);
}

static t_closest_cy		main_solve_cy(t_basic_params *b_par,
		t_cy_ring *ptr_cy, t_closest_cy *result)
{
	t_tmp_params_cy		tmp_params;
	t_vector			tmp_dir;
	t_closest_cy		cur_result;

	cur_result = *result;
	tmp_params = find_cy_wall_points(b_par, &ptr_cy->cy, &cur_result);
	if (tmp_params.err_code == 1)
		return (*result);
	tmp_dir = *b_par->dir;
	vector_scale(&tmp_dir, tmp_params.closest_t);
	tmp_params.inter_cy = vector_sum(*b_par->point,
		tmp_dir);
	cylinder_wall(&tmp_params, &ptr_cy->cy.vector, &cur_result, &ptr_cy->cy);
	tmp_dir = ptr_cy->cy.vector;
	vector_scale(&tmp_dir, -1);
	cylinder_wall(&tmp_params, &tmp_dir, &cur_result, &ptr_cy->cy);
	cl_disc(b_par->point, b_par->dir, &cur_result, &ptr_cy->cy);
	return (cur_result);
}

t_closest_cy			closesst_intersection_cylinder(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene)
{
	t_closest_cy		r;
	t_cy_ring			*ptr_cy;
	t_closest_cy		c_r;
	t_basic_params		b_par;

	b_par.dir = dir;
	b_par.point = point;
	b_par.scene = scene;
	b_par.r_lim = r_lim;
	fill_result(&r, NULL, r_lim->t_max);
	if (scene->cy_ring == NULL)
		return (r);
	ptr_cy = scene->cy_ring;
	while (scene->cy_ring->prev != ptr_cy)
	{
		c_r = main_solve_cy(&b_par, ptr_cy, &r);
		if (c_r.t_closest < r.t_closest && c_r.t_closest > r_lim->t_min)
			r = c_r;
		ptr_cy = ptr_cy->next;
	}
	c_r = main_solve_cy(&b_par, ptr_cy, &r);
	r = (c_r.t_closest < r.t_closest && c_r.t_closest > r_lim->t_min) ? c_r : r;
	ptr_cy = NULL;
	free(ptr_cy);
	return (r);
}
