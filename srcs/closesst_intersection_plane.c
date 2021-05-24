/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   closest_intersection_plane.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/01 16:06:22 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/01 16:06:25 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		check_closest_param(t_pl_ring *ptr_pl, t_coordinates *point,
			t_vector *dir, t_closest_pl *result)
{
	float			t_closest;
	float			a;
	float			b;

	b = vector_dot(*dir, ptr_pl->pl.vector);
	a = vector_dot(vector_substract(*point, ptr_pl->pl.coord),
		ptr_pl->pl.vector);
	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
		return (0);
	t_closest = -a / b;
	if (t_closest < 0.001 || result->t_closest < t_closest)
		return (0);
	result->t_closest = t_closest;
	result->pl = &ptr_pl->pl;
	return (1);
}

t_closest_pl	closesst_intersection_plane(t_coordinates *point, t_vector *dir,
					t_ray_limits *r_lim, t_scene *scene)
{
	t_closest_pl	result;
	t_pl_ring		*ptr_pl;

	result.t_closest = r_lim->t_max;
	result.pl = NULL;
	if (scene->pl_ring == NULL)
		return (result);
	ptr_pl = scene->pl_ring;
	while (scene->pl_ring->prev != ptr_pl)
	{
		if (check_closest_param(ptr_pl, point, dir, &result))
		{
			ptr_pl = ptr_pl->next;
			continue;
		}
		ptr_pl = ptr_pl->next;
	}
	check_closest_param(ptr_pl, point, dir, &result);
	ptr_pl = NULL;
	free(ptr_pl);
	return (result);
}
