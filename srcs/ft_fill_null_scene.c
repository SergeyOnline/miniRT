/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_fill_null_scene.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:51:54 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/19 17:51:57 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_fill_null_scene(t_scene *scene)
{
	scene->res = NULL;
	scene->cam_ring = NULL;
	scene->sp_ring = NULL;
	scene->pl_ring = NULL;
	scene->sq_ring = NULL;
	scene->cy_ring = NULL;
	scene->tr_ring = NULL;
	scene->a_light = NULL;
	scene->light_ring = NULL;
}
