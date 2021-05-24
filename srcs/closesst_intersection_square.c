/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closesst_intersection_square.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 16:27:24 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/01 16:27:26 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		check_closest_param(t_sq_ring *ptr_sq, t_coordinates *point,
		t_vector *dir, t_closest_sq *result)
{
	float			a;
	float			b;
	t_solv_quad		t;
	t_vector		d;
	t_vector		tmp;

	a = vector_dot(vector_substract(*point, ptr_sq->sq.coord),
		ptr_sq->sq.vector);
	b = vector_dot(*dir, ptr_sq->sq.vector);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t.t1 = -a / b;
	tmp = *dir;
	vector_scale(&tmp, t.t1);
	d = vector_substract(vector_sum(tmp, *point), ptr_sq->sq.coord);
	t.t2 = ptr_sq->sq.side / 2;
	if (fabs(d.x) > t.t2 || fabs(d.y) > t.t2 || fabs(d.z) > t.t2)
		return (0);
	if (t.t1 > 0.001 && t.t1 < result->t_closest)
	{
		result->t_closest = t.t1;
		result->sq = &ptr_sq->sq;
	}
	return (1);
}

t_closest_sq	closesst_intersection_square(t_coordinates *point,
		t_vector *dir, t_ray_limits *r_lim, t_scene *scene)
{
	t_closest_sq	result;
	t_sq_ring		*ptr_sq;

	result.t_closest = r_lim->t_max;
	result.sq = NULL;
	if (scene->sq_ring == NULL)
		return (result);
	ptr_sq = scene->sq_ring;
	while (scene->sq_ring->prev != ptr_sq)
	{
		if (check_closest_param(ptr_sq, point, dir, &result))
		{
			ptr_sq = ptr_sq->next;
			continue;
		}
		ptr_sq = ptr_sq->next;
	}
	check_closest_param(ptr_sq, point, dir, &result);
	ptr_sq = NULL;
	free(ptr_sq);
	return (result);
}
