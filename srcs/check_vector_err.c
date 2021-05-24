/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_vector_err.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 10:03:35 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 10:03:38 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_vector_err(char *vector)
{
	int		err;
	int		i;
	char	**tmp;

	tmp = NULL;
	err = 0;
	i = 0;
	tmp = ft_split(vector, ',');
	if ((tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL) || tmp[3] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39mIncorrect VECTOR parameters\n");
		err = 1;
	}
	while (tmp[i++] != NULL)
	{
		if ((ft_is_float(tmp[i - 1])) == 0
			|| (ft_atof(tmp[i - 1]) < -1) || (ft_atof(tmp[i - 1]) > 1))
		{
			ft_putstr("\e[31mError\n\e[39mIncorrect VECTOR parameters\n");
			err = 1;
			break ;
		}
	}
	clear_two_dim_arr(tmp);
	return (err);
}
