/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas_to_viewport.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/09/01 03:58:25 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/09/01 03:58:28 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	canvas_to_viewport(float x, float y, t_scene *scene)
{
	t_vector	v;
	float		width;
	float		height;
	float		image_aspect_ratio;
	float		scale;

	width = (float)scene->res->width;
	height = (float)scene->res->height;
	image_aspect_ratio = width / height;
	scale = tan(deg_to_rad(scene->cam_ring->cam.fov) * 0.5);
	v.x = ((x / (float)width) - 0.5) * image_aspect_ratio * scale;
	v.y = ((y / (float)height) - 0.5) * scale;
	v.z = 1;
	return (v);
}
