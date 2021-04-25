/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 12:26:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/25 20:42:57 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_header_bmp(t_scene *scene, int fd, t_mlx *window)
{
	char	*header;
	int		size;

	size = scene->width * scene->height * 4;
	header = (char *)ft_calloc(sizeof(unsigned char), BMP_HEADER);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned int)(size + BMP_HEADER);
	header[6] = (unsigned short)(0);
	header[8] = (unsigned short)(0);
	header[10] = (unsigned int)(BMP_HEADER);
	header[14] = (unsigned int)(BMP_HEADER - 14);
	header[18] = (unsigned int)(scene->width);
	header[22] = (unsigned int)(scene->height);
	header[26] = (unsigned short)(1);
	header[28] = (unsigned short)(window->image->bpp);
	header[30] = (unsigned int)(0);
	header[34] = (unsigned int)(size);
	header[38] = (unsigned int)(scene->width);
	header[42] = (unsigned int)(scene->height);
	header[46] = (unsigned int)(0);
	header[50] = (unsigned int)(0);
	write(fd, header, BMP_HEADER);
	free(header);
}

void	ft_create_bmp(t_scene *scene, t_mlx *window)
{
	int		fd;
	char	*header;
	int		size;

	size = scene->width * scene->height * 4;
	fd = open("minirt.bmp", O_RDWR | O_CREAT, 0755);
	ft_header_bmp(scene, fd, window);
	write(fd, window->image->data, size);
	close(fd);
}
