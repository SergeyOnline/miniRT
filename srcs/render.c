/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:50:52 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 17:54:59 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	create_cam_to_world(t_matrix44 *cam_rotation, t_scene *scene)
{
	t_vector cam_dir;
	t_vector from_to;
	t_vector tmp;
	t_vector right;
	t_vector up;

	vector_fill(&cam_dir, scene->cam_ring->cam.vector.x,
		scene->cam_ring->cam.vector.y, scene->cam_ring->cam.vector.z);
	from_to = scene->cam_ring->cam.vector;
	if (cam_dir.y == 0)
		vector_fill(&tmp, 0, -1, 0);
	else
		vector_fill(&tmp, 0, 0, 1);
	vector_normalaze(&tmp);
	right = vector_cross(&from_to, &tmp);
	up = vector_cross(&right, &from_to);
	cam_rotation->m[0][0] = right.x;
	cam_rotation->m[0][1] = right.y;
	cam_rotation->m[0][2] = right.z;
	cam_rotation->m[1][0] = up.x;
	cam_rotation->m[1][1] = up.y;
	cam_rotation->m[1][2] = up.z;
	cam_rotation->m[2][0] = from_to.x;
	cam_rotation->m[2][1] = from_to.y;
	cam_rotation->m[2][2] = from_to.z;
}

static void	mlx_pix_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->size_line + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void		render(t_mlx *new_mlx, t_scene *scene)
{
	int				x;
	int				y;
	t_vector		dir;
	t_ray_limits	l;
	t_matrix44		cam_rotation;

	zero_matrix44(&cam_rotation);
	l.t_min = 1;
	l.t_max = FLT_MAX;
	y = -1;
	while (++y < scene->res->height)
	{
		x = -1;
		while (++x < scene->res->width)
		{
			dir = canvas_to_viewport(x, y, scene);
			create_cam_to_world(&cam_rotation, scene);
			dir = mult_dir_matrix(dir, cam_rotation);
			mlx_pix_put(new_mlx->img, x, y,
				trace_ray(&scene->cam_ring->cam.coord, &dir, &l, scene));
		}
	}
	(scene->save == 1) ? save_image(scene, BMP_NAME, new_mlx) :
		mlx_put_image_to_window(new_mlx->mlx,
		new_mlx->window, new_mlx->img->img, 0, 0);
}
