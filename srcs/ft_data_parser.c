/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_data_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/11 13:37:47 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/07/11 13:37:50 by Sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	ft_fill_scene(t_scene *scene, char **data)
{
	if (data[0][0] == 'R' && data[0][1] == '\0')
		return ((handle_resolution(scene, data)) == 1);
	else if (data[0][0] == 'A' && data[0][1] == '\0')
		return ((handle_a_lightning(scene, data)) == 1);
	else if (data[0][0] == 'c' && data[0][1] == '\0')
		return ((handle_cam(scene, data)) == 1);
	else if (data[0][0] == 'l' && data[0][1] == '\0')
		return ((handle_light(scene, data)) == 1);
	else if (data[0][0] == 'p' && data[0][1] == 'l' && data[0][2] == '\0')
		return ((handle_plane(scene, data)) == 1);
	else if (data[0][0] == 's' && data[0][1] == 'p' && data[0][2] == '\0')
		return ((handle_sphere(scene, data)) == 1);
	else if (data[0][0] == 's' && data[0][1] == 'q' && data[0][2] == '\0')
		return ((handle_square(scene, data)) == 1);
	else if (data[0][0] == 'c' && data[0][1] == 'y' && data[0][2] == '\0')
		return ((handle_cylinder(scene, data)) == 1);
	else if (data[0][0] == 't' && data[0][1] == 'r')
		return ((handle_triangle(scene, data)) == 1);
	else if (data[0][0] == '#')
		return (0);
	else
		return (1);
	return (0);
}

static void	check_objs(t_scene *scene)
{
	if (scene->a_light == NULL || scene->res == NULL ||
		scene->cam_ring == NULL)
	{
		ft_clear_scene(scene);
	}
}

static int	check_fd(char *name)
{
	int fd;

	if ((fd = open(name, O_RDONLY)) == -1)
	{
		ft_putstr("\e[31mError\n\e[39mCannot open file scene");
		exit(1);
	}
	return (fd);
}

int			*ft_data_parser(t_scene *scene, char *name)
{
	int		fd;
	char	*line;
	char	**data;
	int		error;

	line = NULL;
	data = NULL;
	fd = check_fd(name);
	while ((get_next_line(fd, &line)) > 0)
	{
		if (!(*line))
		{
			free(line);
			continue;
		}
		data = ft_split(line, ' ');
		free(line);
		error = ft_fill_scene(scene, data);
		clear_two_dim_arr(data);
		(error) ? ft_clear_scene(scene) : 0;
	}
	check_objs(scene);
	free(line);
	(close(fd) == -1) ? exit(1) : 0;
	return (0);
}
