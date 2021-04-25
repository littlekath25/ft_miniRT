/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 12:26:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/25 14:23:13 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_fill_bmp(t_scene *scene, int size, int fd)
{
	int		i;
	int		j;
	int		p;
	int		k;
	char	*data;

	char bitmap[] = {
        255, // Blue
        0, // Green
        255, // Red
        0  // Padding
    };

	i = scene->height;
	data = (char *)ft_calloc(sizeof(unsigned char), size);
	while (i)
	{
		j = 0;
		while (j < scene->width)
		{
			write(fd, &bitmap, sizeof(bitmap));
			j++;
		}
		i--;
	}
	write(fd, data, size);
	free(data);
}

static void	ft_info_bmp(t_scene *scene, int size, int fd, t_mlx *window)
{
	char *info;

	info = (char *)ft_calloc(sizeof(unsigned char), BMP_INFO);
	info[0] = (unsigned char)(BMP_INFO);
	info[4] = (unsigned char)(scene->width);
	info[5] = (unsigned char)(scene->width >> 8);
	info[6] = (unsigned char)(scene->width >> 16);
	info[7] = (unsigned char)(scene->width >> 24);
	info[8] = (unsigned char)(scene->height);
	info[9] = (unsigned char)(scene->height >> 8);
	info[10] = (unsigned char)(scene->height >> 16);
	info[11] = (unsigned char)(scene->height >> 24);
	info[12] = (unsigned char)(1);
	info[14] = (unsigned char)(window->image->bpp);
	info[16] = (unsigned char)(0);
	info[20] = (unsigned char)(size);
	info[24] = (unsigned char)(3780);
	info[28] = (unsigned char)(3780);
	write(fd, info, BMP_INFO);
	free(info);
}

static void	ft_header_bmp(int size, int fd)
{
	char *header;

	header = (char *)ft_calloc(sizeof(unsigned char), BMP_HEADER);
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size + BMP_HEADER + BMP_INFO);
	header[3] = (unsigned char)(size >> 8);
	header[4] = (unsigned char)(size >> 16);
	header[5] = (unsigned char)(size >> 24);
	header[10] = (unsigned char)(BMP_HEADER + BMP_INFO);
	write(fd, header, BMP_HEADER);
	free(header);
}

void	ft_create_bmp(t_scene *scene, t_mlx *window)
{
	int		fd;
	char	*header;
	int		size;

	size = scene->width * scene->height * 3;
	fd = open("minirt.bmp", O_RDWR | O_CREAT, 0755);
	ft_header_bmp(size, fd);
	ft_info_bmp(scene, size, fd, window);
	ft_fill_bmp(scene, size, fd);
	close(fd);
}
