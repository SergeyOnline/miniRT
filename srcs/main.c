/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 12:25:20 by Sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 18:14:58 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static int	pressed_key_to_quit(int keycode)
{
	if (keycode == 12 || keycode == 53)
	{
		ft_putstr("\e[33mBYE!\n\e[39m");
		exit(0);
	}
	return (0);
}

static int	change_cam(int keycode, t_change_cam *params)
{
	if (keycode == 0 || keycode == 123)
	{
		params->scene->cam_ring = params->scene->cam_ring->next;
		render(params->new_mlx, params->scene);
		ft_putstr("\e[36mСamera position changed\n\e[39m");
	}
	if (keycode == 2 || keycode == 124)
	{
		params->scene->cam_ring = params->scene->cam_ring->prev;
		render(params->new_mlx, params->scene);
		ft_putstr("\e[36mСamera position changed\n\e[39m");
	}
	return (0);
}

static int	check_scene_name(char *name, char *rt)
{
	if ((ft_strlen(name)) <= 3)
		return (0);
	if (!(name = (ft_strrchr(name, '.'))))
		return (0);
	while (*name != '\0' || *rt != '\0')
	{
		if (*name != *rt)
			return (0);
		name++;
		rt++;
	}
	if (*name != '\0')
		return (0);
	return (1);
}

static void	check_start_params(int argc, char *argv[], t_scene *scene)
{
	if (argc == 1)
	{
		ft_putstr("\e[31mError\n\e[39mNot enough arguments\n");
		exit(1);
	}
	if (argc > 3)
	{
		ft_putstr("\e[31mError\n\e[39mNumber of arguments exceeded\n");
		exit(1);
	}
	if (argc == 3 && (ft_strncmp(argv[2], "--save", 6) != 0
		|| ft_strlen(argv[2]) != 6))
	{
		ft_putstr("\e[31mError\n\e[39mWrong arguments\n");
		exit(1);
	}
	else if (argc == 3 && ft_strncmp(argv[2], "--save", 6) == 0)
		scene->save = 1;
	if (!(check_scene_name(argv[1], ".rt")))
	{
		ft_putstr("\e[31mError\n\e[39mWrong argument file name\n");
		exit(1);
	}
}

int			main(int argc, char *argv[])
{
	t_mlx			new_mlx;
	t_scene			scene;
	t_img			img;
	t_change_cam	params;

	check_start_params(argc, argv, &scene);
	ft_fill_null_scene(&scene);
	ft_data_parser(&scene, argv[1]);
	new_mlx.mlx = mlx_init();
	new_mlx.window = mlx_new_window(new_mlx.mlx, scene.res->width,
		scene.res->height, "MiniRT");
	img.img = mlx_new_image(new_mlx.mlx, scene.res->width, scene.res->height);
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel,
		&img.size_line, &img.endian);
	new_mlx.img = &img;
	ft_putstr("\e[96mScene file processing successful!\e[39m\n");
	render(&new_mlx, &scene);
	params.new_mlx = &new_mlx;
	params.scene = &scene;
	mlx_hook(new_mlx.window, 2, 0, change_cam, &params);
	mlx_hook(new_mlx.window, 17, 0, close_window, NULL);
	mlx_hook(new_mlx.window, 3, 0, pressed_key_to_quit, NULL);
	if (scene.save == 0)
		mlx_loop(new_mlx.mlx);
	return (0);
}
