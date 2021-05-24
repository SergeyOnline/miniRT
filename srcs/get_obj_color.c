/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_obj_color.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/20 16:20:43 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 15:38:41 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	get_sphere_color(t_closest_sp c_sp,
		t_basic_params *b, t_color correct_color)
{
	t_coordinates	hit_point;
	t_vector		tmp;
	t_vector		norm;
	t_color			corr_color;
	t_basic_params	base;

	tmp = *b->dir;
	vector_scale(&tmp, c_sp.t_closest);
	hit_point = vector_sum(*b->point, tmp);
	norm = vector_substract(hit_point, c_sp.sp->center);
	vector_normalaze(&norm);
	base.dir = b->dir;
	base.point = &hit_point;
	base.scene = b->scene;
	corr_color = compute_lightning(&base, norm, correct_color);
	return (corr_color);
}

t_color	get_plane_color(t_closest_pl c_pl,
		t_basic_params *b, t_color correct_color)
{
	t_coordinates	hit_point;
	t_vector		tmp;
	t_vector		norm;
	t_color			corr_color;
	t_basic_params	base;

	tmp = *b->dir;
	vector_scale(&tmp, c_pl.t_closest);
	hit_point = vector_sum(*b->point, tmp);
	norm = c_pl.pl->vector;
	if ((vector_dot(*b->dir, norm)) > 0)
		vector_scale(&norm, -1);
	vector_normalaze(&norm);
	base.dir = b->dir;
	base.point = &hit_point;
	base.scene = b->scene;
	corr_color = compute_lightning(&base, norm, correct_color);
	return (corr_color);
}

t_color	get_square_color(t_closest_sq c_sq,
		t_basic_params *b, t_color correct_color)
{
	t_coordinates	hit_point;
	t_vector		tmp;
	t_vector		norm;
	t_color			corr_color;
	t_basic_params	base;

	tmp = *b->dir;
	vector_scale(&tmp, c_sq.t_closest);
	hit_point = vector_sum(*b->point, tmp);
	norm = c_sq.sq->vector;
	if ((vector_dot(*b->dir, norm)) > 0)
		vector_scale(&norm, -1);
	vector_normalaze(&norm);
	base.dir = b->dir;
	base.point = &hit_point;
	base.scene = b->scene;
	corr_color = compute_lightning(&base, norm, correct_color);
	return (corr_color);
}

t_color	get_triangle_color(t_closest_tr c_tr,
		t_basic_params *b, t_color correct_color)
{
	t_coordinates		hit_point;
	t_vector			tmp;
	t_color				corr_color;
	t_tmp_cross_param	cross;
	t_basic_params		base;

	tmp = *b->dir;
	vector_scale(&tmp, c_tr.t_closest);
	hit_point = vector_sum(*b->point, tmp);
	cross.cross = vector_substract(c_tr.tr->first, c_tr.tr->second);
	cross.cross2 = vector_substract(c_tr.tr->second, c_tr.tr->third);
	cross.norm = vector_cross(&cross.cross, &cross.cross2);
	if ((vector_dot(*b->dir, cross.norm)) > 0)
		vector_scale(&cross.norm, -1);
	vector_normalaze(&cross.norm);
	base.dir = b->dir;
	base.point = &hit_point;
	base.scene = b->scene;
	corr_color = compute_lightning(&base, cross.norm, correct_color);
	return (corr_color);
}

t_color	get_cylinder_color(t_closest_cy c_cy,
		t_basic_params *b, t_color correct_color)
{
	t_coordinates		hit_point;
	t_tmp_norm_param	n;
	t_basic_params		base;
	t_tmp_cross_param	cross;

	cross.norm = *b->dir;
	vector_scale(&cross.norm, c_cy.t_closest);
	hit_point = vector_sum(*b->point, cross.norm);
	n.norm = vector_substract(hit_point, c_cy.cy->coord);
	n.norm = vector_cross(&n.norm, &c_cy.cy->vector);
	n.norm = vector_cross(&c_cy.cy->vector, &n.norm);
	n.norm_up = c_cy.cy->up_disc.vector;
	n.norm_down = c_cy.cy->down_disc.vector;
	vector_scale(&n.norm_down, -1);
	cross.cross = vector_substract(c_cy.cy->up_disc.center, hit_point);
	if (vector_len(&cross.cross) <= c_cy.cy->diameter / 2)
		n.norm = n.norm_up;
	cross.cross2 = vector_substract(c_cy.cy->down_disc.center, hit_point);
	if (vector_len(&cross.cross2) <= c_cy.cy->diameter / 2)
		n.norm = n.norm_down;
	base.dir = b->dir;
	base.point = &hit_point;
	base.scene = b->scene;
	return (compute_lightning(&base, n.norm, correct_color));
}
