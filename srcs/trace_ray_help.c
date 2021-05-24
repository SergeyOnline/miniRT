/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trace_ray_help.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 15:10:11 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 15:14:18 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	handle_obj_id_sp(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene)
{
	*correct_color = objs->c_sp.sp->color;
	add_amb_color(correct_color, scene);
	*correct_color = get_sphere_color(objs->c_sp, b, *correct_color);
}

void	handle_obj_id_pl(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene)
{
	*correct_color = objs->c_pl.pl->color;
	add_amb_color(correct_color, scene);
	*correct_color = get_plane_color(objs->c_pl, b, *correct_color);
}

void	handle_obj_id_sq(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene)
{
	*correct_color = objs->c_sq.sq->color;
	add_amb_color(correct_color, scene);
	*correct_color = get_square_color(objs->c_sq, b, *correct_color);
}

void	handle_obj_id_tr(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene)
{
	*correct_color = objs->c_tr.tr->color;
	add_amb_color(correct_color, scene);
	*correct_color = get_triangle_color(objs->c_tr, b, *correct_color);
}

void	handle_obj_id_cy(t_color *correct_color,
		t_objects *objs, t_basic_params *b, t_scene *scene)
{
	*correct_color = objs->c_cy.cy->color;
	add_amb_color(correct_color, scene);
	*correct_color = get_cylinder_color(objs->c_cy, b, *correct_color);
}
