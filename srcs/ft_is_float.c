/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_is_float.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/21 13:47:20 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/21 13:47:22 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	ft_strlen(const char *s)
{
	int	index;

	index = 0;
	while (s[index] != '\0')
		index++;
	return (index);
}

static int	ft_isdigit_and_dot(int c)
{
	if ((c >= '0' && c <= '9') || c == '.')
		return (1);
	return (0);
}

int			ft_is_float(char *str)
{
	int i;
	int count_dot;
	int negative;

	count_dot = 0;
	i = 0;
	negative = (str[0] == '-') ? 1 : 0;
	i += (str[0] == '-');
	while (str[i] != '\0')
	{
		count_dot += (str[i] == '.');
		if (count_dot > 1)
			return (0);
		if (i == (0 + negative) || i == ft_strlen(str) - 1)
		{
			if (str[i] == '.')
				return (0);
		}
		if ((ft_isdigit_and_dot(str[i])) == 0)
			return (0);
		i++;
	}
	return (1);
}
