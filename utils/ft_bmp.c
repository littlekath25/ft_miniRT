/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_bmp.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/18 12:26:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/21 18:09:34 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_make_bmp()
{

}

void	ft_create_bmp(int width, int height)
{
	int		fd;
	t_bmp	*bmp;
	
	fd = open("miniRT.bmp", O_CREAT | O_WRONLY);
	bmp = (t_bmp *)ft_calloc(sizeof(t_bmp), 1);
	ft_make_bmp(bmp);
	write(fd, &sign, 2);
	write(fd, &header, sizeof(header));
	close(fd);
}