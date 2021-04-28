/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 12:26:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/28 15:47:08 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_header_bmp(t_scene *scene, int fd, t_img *img, int size)
{
	char				*header;

	header = (char *)ft_calloc(sizeof(unsigned char), BMP_HEADER);
	if (header == NULL)
		ft_error_and_exit(3, "BMP Header - ");
	*((unsigned char *)(header)) = (unsigned char)('B');
	*((unsigned char *)(header + 1)) = (unsigned char)('M');
	*((unsigned int *)(header + 2)) = (unsigned int)(size + BMP_HEADER);
	*((unsigned short *)(header + 6)) = (unsigned short)(0);
	*((unsigned short *)(header + 8)) = (unsigned short)(0);
	*((unsigned int *)(header + 10)) = (unsigned int)(BMP_HEADER);
	*((unsigned int *)(header + 14)) = (unsigned int)(BMP_HEADER - 14);
	*((unsigned int *)(header + 18)) = (unsigned int)(scene->width);
	*((unsigned int *)(header + 22)) = (unsigned int)(scene->height);
	*((unsigned short *)(header + 26)) = (unsigned short)(1);
	*((unsigned short *)(header + 28)) = (unsigned short)(img->bpp);
	*((unsigned int *)(header + 30)) = (unsigned int)(0);
	*((unsigned int *)(header + 34)) = (unsigned int)(size);
	*((unsigned int *)(header + 38)) = (unsigned int)(scene->width);
	*((unsigned int *)(header + 42)) = (unsigned int)(scene->height);
	*((unsigned int *)(header + 46)) = (unsigned int)(0);
	*((unsigned int *)(header + 50)) = (unsigned int)(0);
	write(fd, header, BMP_HEADER);
	free(header);
}

void	ft_create_bmp(t_scene *scene, t_img *img)
{
	int		fd;
	int		size;

	size = scene->width * scene->height * 4;
	fd = open("minirt.bmp", O_RDWR | O_CREAT, 0755);
	ft_header_bmp(scene, fd, img, size);
	write(fd, img->data, size);
	close(fd);
}
