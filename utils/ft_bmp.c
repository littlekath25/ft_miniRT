/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 12:26:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/23 20:26:19 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_header_bmp(char *info, int size)
{
	info[0] = 'B';
	info[1] = 'M';
	info[2] = size + BMP_HEADER;
}

void	ft_create_bmp(int width, int height)
{
	int		fd;
	char	*info;
	int		size;

	size = width * height * 3;
	info = (char *)ft_calloc(size + BMP_HEADER, 1);
	fd = open("minirt.bmp", O_RDWR | O_CREAT, 0755);
	ft_header_bmp(info, size);
	write(fd, info, sizeof(info));
	free(info);
	close(fd);
}
