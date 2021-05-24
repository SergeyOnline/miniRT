/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closesst_intersection_triangle.c                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 16:43:38 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/01 16:43:40 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		check_closest_param(t_tr_ring *ptr_tr, t_coordinates *point,
t_vector *dir, t_closest_tr *result)
{
	t_tr_coeffs		coeff;
	t_vector		p_vec;
	t_vector		t_vec;

	coeff.v1 = vector_substract(ptr_tr->tr.second, ptr_tr->tr.first);
	coeff.v2 = vector_substract(ptr_tr->tr.third, ptr_tr->tr.first);
	p_vec = vector_cross(dir, &coeff.v2);
	coeff.det = vector_dot(coeff.v1, p_vec);
	if (fabs(coeff.det) < 0.00001)
		return (0);
	coeff.c = 1 / coeff.det;
	t_vec = vector_substract(*point, ptr_tr->tr.first);
	coeff.a = vector_dot(t_vec, p_vec) * coeff.c;
	if (coeff.a < 0 || coeff.a > 1)
		return (0);
	t_vec = vector_cross(&t_vec, &coeff.v1);
	coeff.b = vector_dot(*dir, t_vec) * coeff.c;
	if (coeff.b < 0 || coeff.a + coeff.b > 1)
		return (0);
	if (vector_dot(coeff.v2, t_vec) * coeff.c < 0.001)
		return (0);
	result->t_closest = vector_dot(coeff.v2, t_vec) * coeff.c;
	result->tr = &ptr_tr->tr;
	return (1);
}

t_closest_tr	closesst_intersection_triangle(t_coordinates *point,
	t_vector *dir, t_ray_limits *r_lim, t_scene *scene)
{
	t_closest_tr	result;
	t_tr_ring		*ptr_tr;

	result.t_closest = r_lim->t_max;
	result.tr = NULL;
	if (scene->tr_ring == NULL)
		return (result);
	ptr_tr = scene->tr_ring;
	while (scene->tr_ring->prev != ptr_tr)
	{
		if (check_closest_param(ptr_tr, point, dir, &result))
		{
			ptr_tr = ptr_tr->next;
			continue;
		}
		ptr_tr = ptr_tr->next;
	}
	check_closest_param(ptr_tr, point, dir, &result);
	ptr_tr = NULL;
	free(ptr_tr);
	return (result);
}
