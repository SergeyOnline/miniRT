/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_clear_scene.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/19 17:52:16 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/19 17:52:17 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_clear_scene(t_scene *scene)
{
	free(scene->a_light);
	scene->a_light = NULL;
	free(scene->res);
	scene->res = NULL;
	clear_light_ring(&scene->light_ring);
	clear_cam_ring(&scene->cam_ring);
	clear_cy_ring(&scene->cy_ring);
	clear_pl_ring(&scene->pl_ring);
	clear_sp_ring(&scene->sp_ring);
	clear_sq_ring(&scene->sq_ring);
	clear_tr_ring(&scene->tr_ring);
	ft_putstr("\e[31mError\n\e[39mIncorrect input data");
	exit(1);
}
