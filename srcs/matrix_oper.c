/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_oper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/21 13:57:53 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/08/21 13:57:55 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector		mult_dir_matrix(t_vector vec, t_matrix44 matrix)
{
	t_vector	result;
	float		a;
	float		b;
	float		c;

	a = vec.x * matrix.m[0][0] + vec.y * matrix.m[1][0] +
		vec.z * matrix.m[2][0];
	b = vec.x * matrix.m[0][1] + vec.y * matrix.m[1][1] +
		vec.z * matrix.m[2][1];
	c = vec.x * matrix.m[0][2] + vec.y * matrix.m[1][2] +
		vec.z * matrix.m[2][2];
	result.x = a;
	result.y = b;
	result.z = c;
	return (result);
}
