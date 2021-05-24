/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_all_digit.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/30 18:13:17 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/04/30 18:13:23 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int			ft_is_all_digit(char *str)
{
	int i;

	i = 0;
	while (str[i] != '\0')
	{
		if ((ft_isdigit(str[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}
