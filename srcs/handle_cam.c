/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cam.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 15:22:21 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/21 15:22:22 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_errors(char **data)
{
	int err;

	err = 0;
	if (data[4] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect number of \"CAMERA\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	err = (err == 0) ? check_vector_err(data[2]) : err;
	if ((ft_is_all_digit(data[3])) == 0 || (ft_atoi(data[3]) < 0)
		|| (ft_atoi(data[3]) >= 180))
	{
		ft_putstr("\e[31mError\n\e[39mWrong camera parameters\n");
		err = 1;
	}
	return (err);
}

int			handle_cam(t_scene *scene, char **data)
{
	char		**temp;
	int			err;
	t_camera	cam;

	temp = NULL;
	err = check_errors(data);
	if (err)
		return (err);
	temp = ft_split(data[1], ',');
	cam.coord.x = ft_atof(temp[0]);
	cam.coord.y = ft_atof(temp[1]);
	cam.coord.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[2], ',');
	cam.vector.x = ft_atof(temp[0]);
	cam.vector.y = ft_atof(temp[1]);
	cam.vector.z = ft_atof(temp[2]);
	cam.fov = ft_atof(data[3]);
	add_element_cam_ring(&(scene->cam_ring), cam);
	clear_two_dim_arr(temp);
	return (err);
}
