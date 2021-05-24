/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_resolution.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/20 12:20:17 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/20 12:20:19 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#define MAX_HEIGHT 1440
#define MAX_WIDTH 2560

static int	check_errors(char **data, t_resolution **res)
{
	int err;

	err = 0;
	if (data[3] != NULL || ((ft_is_all_digit(data[1])) == 0)
			|| ((ft_is_all_digit(data[2])) == 0))
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect \"RESOLUTION\" parameters\n");
		err = 1;
	}
	if ((*res)->height < 1 || (*res)->width < 1)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect resolution height/width\n");
		err = 1;
	}
	if ((*res)->height > MAX_HEIGHT)
		(*res)->height = MAX_HEIGHT;
	if ((*res)->width > MAX_WIDTH)
		(*res)->width = MAX_WIDTH;
	return (err);
}

int			handle_resolution(t_scene *scene, char **data)
{
	int				err;
	t_resolution	*res;

	res = (t_resolution *)malloc(sizeof(*res));
	res->height = ft_atoi(data[2]);
	res->width = ft_atoi(data[1]);
	scene->res = res;
	err = check_errors(data, &res);
	if (err)
	{
		res = NULL;
		free(res);
		return (err);
	}
	res = NULL;
	free(res);
	return (err);
}
