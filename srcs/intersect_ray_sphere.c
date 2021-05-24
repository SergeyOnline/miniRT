/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_ray_sphere.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 16:03:46 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/08/31 16:03:49 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_solv_quad	intersect_ray_sphere(t_vector *orig, t_vector *dir, t_sphere *sp)
{
	t_solv_quad		solv_quad;
	t_quad_coeffs	coeffs;
	float			radius;
	t_vector		oc;

	oc = vector_substract(*orig, sp->center);
	radius = sp->diameter * 0.5;
	coeffs.k1 = vector_dot(*dir, *dir);
	coeffs.k2 = 2 * vector_dot(oc, *dir);
	coeffs.k3 = vector_dot(oc, oc) - radius * radius;
	coeffs.discr = coeffs.k2 * coeffs.k2 - 4 * coeffs.k1 * coeffs.k3;
	if (coeffs.discr < 0)
	{
		solv_quad.t1 = FLT_MAX;
		solv_quad.t2 = FLT_MAX;
		return (solv_quad);
	}
	solv_quad.t1 = (-coeffs.k2 + sqrt(coeffs.discr)) / (2 * coeffs.k1);
	solv_quad.t2 = (-coeffs.k2 - sqrt(coeffs.discr)) / (2 * coeffs.k1);
	return (solv_quad);
}
