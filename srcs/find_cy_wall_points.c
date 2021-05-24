/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_cy_wall_points.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 12:56:20 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/02 12:56:23 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void			solve_quad_params(t_quad_coeffs *s,
	t_coordinates *point, t_vector *dir, t_cylinder *cy)
{
	t_vector			cross_cy;
	t_vector			sub;
	t_vector			cross_cy2;

	cross_cy = vector_cross(dir, &cy->vector);
	sub = vector_substract(*point, cy->coord);
	cross_cy2 = vector_cross(&sub, &cy->vector);
	s->k1 = vector_dot(cross_cy, cross_cy);
	s->k2 = 2 * vector_dot(cross_cy, cross_cy2);
	s->k3 = vector_dot(cross_cy2, cross_cy2) -
		(pow(cy->diameter / 2, 2) *
		vector_dot(cy->vector, cy->vector));
	s->discr = pow(s->k2, 2) - (4 * s->k1 * s->k3);
	s->k1 *= 2;
}

void				fill_result(t_closest_cy *result,
	t_cylinder *cy, float t_closesst)
{
	result->t_closest = t_closesst;
	result->cy = cy;
}

t_tmp_params_cy		find_cy_wall_points(t_basic_params *b_par,
		t_cylinder *cy, t_closest_cy *result)
{
	t_tmp_params_cy		t_p;
	t_quad_coeffs		s;

	t_p.err_code = 0;
	solve_quad_params(&s, b_par->point, b_par->dir, cy);
	t_p.err_code = (s.discr < 0) ? 1 : t_p.err_code;
	t_p.err_code = (s.k1 == 0) ? 1 : t_p.err_code;
	if (t_p.err_code == 1)
		return (t_p);
	s.discr = sqrt(s.discr);
	t_p.solve_quad.t1 = (-s.k2 - s.discr) / s.k1;
	t_p.solve_quad.t2 = (-s.k2 + s.discr) / s.k1;
	t_p.closest_t = b_par->r_lim->t_max;
	if (t_p.solve_quad.t1 >= 0 && t_p.solve_quad.t1 <= result->t_closest)
		t_p.closest_t = t_p.solve_quad.t1;
	else if (t_p.solve_quad.t2 >= 0 && t_p.solve_quad.t2 <= result->t_closest)
		t_p.closest_t = t_p.solve_quad.t2;
	if (t_p.closest_t == b_par->r_lim->t_max)
	{
		t_p.err_code = 1;
		return (t_p);
	}
	result->t_closest = t_p.closest_t;
	result->cy = cy;
	return (t_p);
}
