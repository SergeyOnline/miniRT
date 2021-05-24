/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_triangle.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 12:21:53 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 12:21:55 by Sbroderi         ###   ########.fr       */
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
		ft_putstr("Incorrect number of \"TRIANGLE\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	err = (err == 0) ? check_coord_err(data[2]) : err;
	err = (err == 0) ? check_coord_err(data[3]) : err;
	err = (err == 0) ? check_color_err(data[4]) : err;
	return (err);
}

static void	fill_color(t_triangle *tr, char **data)
{
	tr->color.red = ft_atoi(data[0]);
	tr->color.green = ft_atoi(data[1]);
	tr->color.blue = ft_atoi(data[2]);
}

static void	fill_first(t_triangle *tr, char **data)
{
	tr->first.x = ft_atof(data[0]);
	tr->first.y = ft_atof(data[1]);
	tr->first.z = ft_atof(data[2]);
}

int			handle_triangle(t_scene *scene, char **data)
{
	t_triangle	tr;
	int			err;
	char		**temp;

	err = check_errors(data);
	if (err)
		return (err);
	temp = ft_split(data[1], ',');
	fill_first(&tr, temp);
	clear_two_dim_arr(temp);
	temp = ft_split(data[2], ',');
	tr.second.x = ft_atof(temp[0]);
	tr.second.y = ft_atof(temp[1]);
	tr.second.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[3], ',');
	tr.third.x = ft_atof(temp[0]);
	tr.third.y = ft_atof(temp[1]);
	tr.third.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[4], ',');
	fill_color(&tr, temp);
	add_element_tr_ring(&(scene->tr_ring), tr);
	clear_two_dim_arr(temp);
	return (err);
}
