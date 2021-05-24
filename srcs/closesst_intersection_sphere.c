/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closesst_intersection_sphere.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 16:24:28 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/01 16:24:31 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void		check_closest_param(t_sp_ring *ptr_sp, t_ray_limits *r_lim,
					t_solv_quad *solv_quad, t_closest_sp *result)
{
	if (solv_quad->t1 > r_lim->t_min && solv_quad->t1 < r_lim->t_max
		&& solv_quad->t1 < result->t_closest)
	{
		result->t_closest = solv_quad->t1;
		result->sp = &ptr_sp->sp;
	}
	if (solv_quad->t2 > r_lim->t_min && solv_quad->t2 < r_lim->t_max
		&& solv_quad->t2 < result->t_closest)
	{
		result->t_closest = solv_quad->t2;
		result->sp = &ptr_sp->sp;
	}
}

t_closest_sp	closesst_intersection_sphere(t_coordinates *point,
					t_vector *dir, t_ray_limits *r_lim, t_scene *scene)
{
	t_solv_quad		solv_quad;
	t_closest_sp	result;
	t_sp_ring		*ptr_sp;

	result.t_closest = r_lim->t_max;
	result.sp = NULL;
	if (scene->sp_ring == NULL)
		return (result);
	ptr_sp = scene->sp_ring;
	while (scene->sp_ring->prev != ptr_sp)
	{
		solv_quad = intersect_ray_sphere(point, dir, &ptr_sp->sp);
		check_closest_param(ptr_sp, r_lim, &solv_quad, &result);
		ptr_sp = ptr_sp->next;
	}
	solv_quad = intersect_ray_sphere(point, dir, &ptr_sp->sp);
	check_closest_param(ptr_sp, r_lim, &solv_quad, &result);
	ptr_sp = NULL;
	free(ptr_sp);
	return (result);
}
