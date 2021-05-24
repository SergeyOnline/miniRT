/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_cylinder.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 11:30:36 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 11:30:38 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int		check_errors(char **data)
{
	int	err;

	err = 0;
	if (data[6] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39m");
		ft_putstr("Incorrect number of \"CYLINDER\" parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_coord_err(data[1]) : err;
	err = (err == 0) ? check_vector_err(data[2]) : err;
	if ((ft_is_float(data[3])) == 0 || (ft_atof(data[3]) <= 0)
		|| (ft_is_float(data[4])) == 0 || (ft_atof(data[4]) <= 0))
	{
		ft_putstr("\e[31mError\n\e[39mIncorrect cylinder parameters\n");
		err = 1;
	}
	err = (err == 0) ? check_color_err(data[5]) : err;
	return (err);
}

static void		fill_color(t_cylinder *cy, char **data)
{
	cy->color.red = ft_atoi(data[0]);
	cy->color.green = ft_atoi(data[1]);
	cy->color.blue = ft_atoi(data[2]);
}

static void		find_cy_discs(t_cylinder *cy)
{
	t_vector		orientation;
	t_vector		tmp;

	cy->up_disc.color = cy->color;
	cy->down_disc.color = cy->color;
	cy->up_disc.diameter = cy->diameter;
	cy->down_disc.diameter = cy->diameter;
	tmp.x = fabsf(cy->vector.x);
	tmp.y = fabsf(cy->vector.y);
	tmp.z = fabsf(cy->vector.z);
	vector_scale(&tmp, cy->height / 2);
	cy->up_disc.center = vector_sum(cy->coord, tmp);
	tmp.x = fabsf(cy->vector.x);
	tmp.y = fabsf(cy->vector.y);
	tmp.z = fabsf(cy->vector.z);
	vector_scale(&tmp, -cy->height / 2);
	cy->down_disc.center = vector_sum(cy->coord, tmp);
	(cy->vector.y < 1 && cy->vector.y > -1) ?
		vector_fill(&orientation, 0, 1, 0) : vector_fill(&orientation, 1, 0, 0);
	cy->up_disc.vector = vector_cross(&cy->vector, &orientation);
	cy->up_disc.vector = vector_cross(&orientation, &cy->up_disc.vector);
	cy->down_disc.vector = cy->up_disc.vector;
}

int				handle_cylinder(t_scene *scene, char **data)
{
	t_cylinder	cy;
	char		**temp;
	int			err;

	temp = NULL;
	if ((err = check_errors(data)))
		return (err);
	temp = ft_split(data[1], ',');
	cy.coord.x = ft_atof(temp[0]);
	cy.coord.y = ft_atof(temp[1]);
	cy.coord.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	temp = ft_split(data[2], ',');
	cy.vector.x = ft_atof(temp[0]);
	cy.vector.y = ft_atof(temp[1]);
	cy.vector.z = ft_atof(temp[2]);
	clear_two_dim_arr(temp);
	cy.diameter = ft_atof(data[3]);
	cy.height = ft_atof(data[4]);
	temp = ft_split(data[5], ',');
	fill_color(&cy, temp);
	find_cy_discs(&cy);
	add_element_cy_ring(&(scene->cy_ring), cy);
	clear_two_dim_arr(temp);
	return (err);
}
