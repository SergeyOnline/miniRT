/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_object_help.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 14:52:27 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 14:52:29 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	find_cy(t_cl_obj_par *param, t_objects *objects)
{
	param->color = objects->c_cy.cy->color;
	param->closest_t = objects->c_cy.t_closest;
	param->obj_id = CYLINDER;
}

void	find_sp(t_cl_obj_par *param, t_objects *objects)
{
	param->color = objects->c_sp.sp->color;
	param->closest_t = objects->c_sp.t_closest;
	param->obj_id = SPHERE;
}

void	find_sq(t_cl_obj_par *param, t_objects *objects)
{
	param->color = objects->c_sq.sq->color;
	param->closest_t = objects->c_sq.t_closest;
	param->obj_id = SQUARE;
}

void	find_pl(t_cl_obj_par *param, t_objects *objects)
{
	param->color = objects->c_pl.pl->color;
	param->closest_t = objects->c_pl.t_closest;
	param->obj_id = PLANE;
}

void	find_tr(t_cl_obj_par *param, t_objects *objects)
{
	param->color = objects->c_tr.tr->color;
	param->closest_t = objects->c_tr.t_closest;
	param->obj_id = TRIANGLE;
}
