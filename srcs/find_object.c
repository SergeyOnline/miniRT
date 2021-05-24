/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_object.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:40:02 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 14:40:04 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_cl_obj_par	find_object(t_objects objects)
{
	t_cl_obj_par	param;

	param.closest_t = FLT_MAX;
	if (objects.c_cy.t_closest < param.closest_t)
		find_cy(&param, &objects);
	if (objects.c_sp.t_closest < param.closest_t)
		find_sp(&param, &objects);
	if (objects.c_sq.t_closest < param.closest_t)
		find_sq(&param, &objects);
	if (objects.c_pl.t_closest < param.closest_t)
		find_pl(&param, &objects);
	if (objects.c_tr.t_closest < param.closest_t)
		find_tr(&param, &objects);
	return (param);
}
