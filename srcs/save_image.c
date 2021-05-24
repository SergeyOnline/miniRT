/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbroderi <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/15 17:45:31 by sbroderi          #+#    #+#             */
/*   Updated: 2020/10/15 17:49:28 by sbroderi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

static void	file_header(t_scene *scene, t_mlx *mlx, int size, int fd)
{
	unsigned char	*file_header;
	int				file_size;
	unsigned		*ptr;

	if (!(file_header = ft_calloc(BMP_FILE_HEADER, sizeof(unsigned char))))
		exit(1);
	file_size = BMP_FILE_HEADER + BMP_INFO_HEADER +
		(mlx->img->bits_per_pixel / 8 * scene->res->width + size) *
		scene->res->height;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	ptr = (unsigned *)(file_header + 2);
	*ptr = file_size;
	file_header[10] = (unsigned char)(BMP_FILE_HEADER + BMP_INFO_HEADER);
	write(fd, file_header, BMP_FILE_HEADER);
	free(file_header);
}

static void	info_header(t_scene *scene, t_mlx *mlx, int fd)
{
	unsigned char	*info_header;
	unsigned		*ptr;

	if (!(info_header = ft_calloc(BMP_INFO_HEADER, sizeof(unsigned char))))
		exit(1);
	info_header[0] = (unsigned char)(BMP_INFO_HEADER);
	ptr = (unsigned *)(info_header + 4);
	*ptr = scene->res->width;
	ptr = (unsigned *)(info_header + 8);
	*ptr = scene->res->height;
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(mlx->img->bits_per_pixel);
	write(fd, info_header, BMP_INFO_HEADER);
	free(info_header);
}

void		save_image(t_scene *scene, char *name, t_mlx *mlx)
{
	int				fd;
	int				size;
	unsigned char	pad[3];
	int				x;
	int				y;

	ft_memset(pad, 0, 3);
	if (!(fd = open(name, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		exit(1);
	size = (4 - (scene->res->width * mlx->img->bits_per_pixel / 8) % 4) % 4;
	file_header(scene, mlx, size, fd);
	info_header(scene, mlx, fd);
	y = scene->res->height;
	while (--y >= 0)
	{
		x = -1;
		while (++x < scene->res->width)
		{
			write(fd, mlx->img->addr + (y * mlx->img->size_line +
				x * (mlx->img->bits_per_pixel / 8)), sizeof(unsigned int));
			write(fd, pad, size);
		}
	}
	close(fd);
}
