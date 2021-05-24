/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color_operations.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 13:47:57 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/13 13:47:59 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	transform_color_to_vector(t_color *color, t_vector *col_vec)
{
	col_vec->x = (float)color->red / 255;
	col_vec->y = (float)color->green / 255;
	col_vec->z = (float)color->blue / 255;
}

void	color_correct(t_vector *color)
{
	if (color->x > 1)
		color->x = 1;
	if (color->y > 1)
		color->y = 1;
	if (color->z > 1)
		color->z = 1;
}
