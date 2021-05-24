/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_plane.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:38:34 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 10:38:36 by Sbroderi         ###   ########.fr       */
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
		ft_putstr("Incorrect number of \"PLANE\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	err = (err == 0) ? check_vector_err(data[2]) : err;
	err = (err == 0) ? check_color_err(data[3]) : err;
	return (err);
}

int			handle_plane(t_scene *scene, char **data)
{
	t_plane	pl;
	char	**temp;
	int		err;

	err = check_errors(data);
	if (err)
		return (err);
	temp = ft_split(data[1], ',');
	pl.coord.x = ft_atof(temp[0]);
	pl.coord.y = ft_atof(temp[1]);
	pl.coord.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[2], ',');
	pl.vector.x = ft_atof(temp[0]);
	pl.vector.y = ft_atof(temp[1]);
	pl.vector.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[3], ',');
	pl.color.red = ft_atoi(temp[0]);
	pl.color.green = ft_atoi(temp[1]);
	pl.color.blue = ft_atoi(temp[2]);
	add_element_pl_ring(&(scene->pl_ring), pl);
	clear_two_dim_arr(temp);
	return (err);
}
