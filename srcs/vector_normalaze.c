/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_normalaze.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/31 14:58:04 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/08/31 14:58:06 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	vector_normalaze(t_vector *vect)
{
	float	len;
	float	inv_len;

	len = vect->x * vect->x + vect->y * vect->y + vect->z * vect->z;
	if (len > 0)
	{
		inv_len = 1 / sqrtf(len);
		vect->x *= inv_len;
		vect->y *= inv_len;
		vect->z *= inv_len;
	}
}
