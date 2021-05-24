/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_light.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:16:03 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 10:16:05 by Sbroderi         ###   ########.fr       */
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
		ft_putstr("Incorrect number of \"LIGHTNING\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	if ((ft_is_float(data[2])) == 0 || (ft_atof(data[2]) < 0)
		|| (ft_atof(data[2]) > 1))
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect lightning parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_color_err(data[3]) : err;
	return (err);
}

int			handle_light(t_scene *scene, char **data)
{
	t_light	light;
	char	**temp;
	int		err;

	temp = NULL;
	err = check_errors(data);
	if (err)
		return (err);
	temp = ft_split(data[1], ',');
	light.coord.x = ft_atof(temp[0]);
	light.coord.y = ft_atof(temp[1]);
	light.coord.z = ft_atof(temp[2]);
	light.b_ratio = ft_atof(data[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[3], ',');
	light.color.red = ft_atoi(temp[0]);
	light.color.green = ft_atoi(temp[1]);
	light.color.blue = ft_atoi(temp[2]);
	add_element_light_ring(&(scene->light_ring), light);
	clear_two_dim_arr(temp);
	return (err);
}
