/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_color_err.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/22 09:55:48 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/22 09:55:52 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	check_color_err(char *color)
{
	int		err;
	int		i;
	char	**tmp;

	tmp = NULL;
	err = 0;
	i = 0;
	tmp = ft_split(color, ',');
	if ((tmp[0] == NULL || tmp[1] == NULL || tmp[2] == NULL) || tmp[3] != NULL)
	{
		ft_putstr("\e[31mError\n\e[39mIncorrect number of COLOR parameters\n");
		err = 1;
	}
	while (tmp[i++] != NULL)
	{
		if ((ft_is_all_digit(tmp[i - 1])) == 0
			|| (ft_atoi(tmp[i - 1]) < 0) || (ft_atoi(tmp[i - 1]) > 255))
		{
			ft_putstr("\e[31mError\n\e[39mIncorrect COLOR parameters\n");
			err = 1;
			break ;
		}
	}
	clear_two_dim_arr(tmp);
	return (err);
}
