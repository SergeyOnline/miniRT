/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_square.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:52:07 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 10:52:09 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_errors(char **data)
{
	int	err;

	err = 0;
	if (data[5] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect number of \"SQUARE\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	err = (err == 0) ? check_vector_err(data[2]) : err;
	if ((ft_is_float(data[3])) == 0 || (ft_atof(data[3]) <= 0))
	{
		ft_putstr("\e[31mError\n\e[39mIncorrect square parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_color_err(data[4]) : err;
	return (err);
}

int			handle_square(t_scene *scene, char **data)
{
	t_square	sq;
	char		**temp;
	int			err;

	err = check_errors(data);
	if (err)
		return (err);
	temp = ft_split(data[1], ',');
	sq.coord.x = ft_atof(temp[0]);
	sq.coord.y = ft_atof(temp[1]);
	sq.coord.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[2], ',');
	sq.vector.x = ft_atof(temp[0]);
	sq.vector.y = ft_atof(temp[1]);
	sq.vector.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	sq.side = ft_atof(data[3]);
	temp = ft_split(data[4], ',');
	sq.color.red = ft_atoi(temp[0]);
	sq.color.green = ft_atoi(temp[1]);
	sq.color.blue = ft_atoi(temp[2]);
	add_element_sq_ring(&(scene->sq_ring), sq);
	clear_two_dim_arr(temp);
	return (err);
}
