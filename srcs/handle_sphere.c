/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_sphere.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:20:38 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 11:20:40 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_errors(char **data)
{
	int	err;

	err = 0;
	if (data[4] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect number of \"SPHERE\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	if ((ft_is_float(data[2])) == 0 || (ft_atof(data[2]) <= 0))
	{
		ft_putstr("\e[31mError\n\e[39mIncorrect sphere parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_color_err(data[3]) : err;
	return (err);
}

int			handle_sphere(t_scene *scene, char **data)
{
	t_sphere	sp;
	char		**temp;
	int			err;

	err = check_errors(data);
	if (err)
		return (err);
	temp = NULL;
	temp = ft_split(data[1], ',');
	sp.center.x = ft_atof(temp[0]);
	sp.center.y = ft_atof(temp[1]);
	sp.center.z = ft_atof(temp[2]);
	sp.diameter = ft_atof(data[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[3], ',');
	sp.color.red = ft_atoi(temp[0]);
	sp.color.green = ft_atoi(temp[1]);
	sp.color.blue = ft_atoi(temp[2]);
	add_element_sp_ring(&(scene->sp_ring), sp);
	clear_two_dim_arr(temp);
	return (err);
}
