/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_a_lightning.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:16:41 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/21 13:16:43 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	check_errors(char **data)
{
	int	err;

	err = 0;
	if (data[3] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect number of \"A LIGHTNING\" parameters\n");
		err = 1;
	}
	if ((ft_is_float(data[1])) == 0 || (ft_atof(data[1]) < 0)
		|| (ft_atof(data[1]) > 1))
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Wrong ambient lightning parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_color_err(data[2]) : err;
	return (err);
}

int			handle_a_lightning(t_scene *scene, char **data)
{
	char			**temp;
	int				err;
	t_a_lightning	*a_light;

	temp = NULL;
	err = check_errors(data);
	if (err)
		return (err);
	a_light = (t_a_lightning *)malloc(sizeof(*a_light));
	a_light->ratio = ft_atof(data[1]);
	temp = ft_split(data[2], ',');
	a_light->color.red = ft_atoi(temp[0]);
	a_light->color.green = ft_atoi(temp[1]);
	a_light->color.blue = ft_atoi(temp[2]);
	scene->a_light = a_light;
	a_light = NULL;
	clear_two_dim_arr(temp);
	free(a_light);
	return (err);
}
