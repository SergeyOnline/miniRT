/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compute_lightning.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 01:27:57 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 12:55:16 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		find_closesst_obj(t_params_light_calc *params,
		t_scene *scene, t_vector *l)
{
	t_closest_sp	shadow_sp;
	t_closest_pl	shadow_pl;
	t_closest_sq	shadow_sq;
	t_closest_tr	shadow_tr;
	t_closest_cy	shadow_cy;

	shadow_sp = closesst_intersection_sphere(params->point,
		l, params->r_lim, scene);
	shadow_pl = closesst_intersection_plane(params->point,
		l, params->r_lim, scene);
	shadow_sq = closesst_intersection_square(params->point,
		l, params->r_lim, scene);
	shadow_tr = closesst_intersection_triangle(params->point,
		l, params->r_lim, scene);
	shadow_cy = closesst_intersection_cylinder(params->point,
		l, params->r_lim, scene);
	if ((shadow_sp.sp != NULL && shadow_sp.t_closest < 1) ||
		(shadow_tr.tr != NULL && shadow_tr.t_closest < 1) ||
		(shadow_sq.sq != NULL && shadow_sq.t_closest < 1) ||
		(shadow_cy.cy != NULL && shadow_cy.t_closest < 1) ||
		(shadow_pl.pl != NULL && shadow_pl.t_closest < 1))
		return (0);
	return (1);
}

static float	check_shadows_defuseness(t_params_light_calc *params,
		t_light_ring *ptr_light, t_scene *scene)
{
	t_vector		light;
	float			n_dot_l;

	light = vector_substract(ptr_light->light.coord, *params->point);
	if (find_closesst_obj(params, scene, &light) == 0)
		return (FLT_MAX);
	n_dot_l = vector_dot(*params->normal, light);
	n_dot_l = ptr_light->light.b_ratio * n_dot_l /
		(vector_len(params->normal) * vector_len(&light));
	return (n_dot_l);
}

static t_color	transform_color_to_int(t_vector color)
{
	t_color	correct_color;

	correct_color.red = (int)(color.x * 255);
	correct_color.green = (int)(color.y * 255);
	correct_color.blue = (int)(color.z * 255);
	return (correct_color);
}

static void		main_comp_light(t_basic_params *base,
		t_params_light_calc *params, t_light_ring *ptr_light, t_vector *col_vec)
{
	float		n_dot_l;
	t_vector	light_vec;

	n_dot_l = check_shadows_defuseness(params, ptr_light, base->scene);
	transform_color_to_vector(&ptr_light->light.color, &light_vec);
	vector_normalaze(&light_vec);
	vector_scale(&light_vec, ptr_light->light.b_ratio);
	if (n_dot_l > 0 && n_dot_l <= 1)
	{
		vector_scale(&light_vec, n_dot_l);
		*col_vec = vector_sum(*col_vec, light_vec);
		color_correct(col_vec);
	}
}

t_color			compute_lightning(t_basic_params *base,
		t_vector normal, t_color color)
{
	t_params_light_calc	params;
	t_light_ring		*ptr_light;
	t_vector			col_vec;
	t_ray_limits		lim;

	lim.t_max = 1.0;
	lim.t_min = 0.1;
	params.dir = base->dir;
	params.normal = &normal;
	params.point = base->point;
	params.r_lim = &lim;
	ptr_light = base->scene->light_ring;
	transform_color_to_vector(&color, &col_vec);
	if (base->scene->light_ring == NULL)
		return (transform_color_to_int(col_vec));
	while (base->scene->light_ring->prev != ptr_light)
	{
		main_comp_light(base, &params, ptr_light, &col_vec);
		ptr_light = ptr_light->next;
	}
	main_comp_light(base, &params, ptr_light, &col_vec);
	ptr_light = NULL;
	free(ptr_light);
	return (transform_color_to_int(col_vec));
}
