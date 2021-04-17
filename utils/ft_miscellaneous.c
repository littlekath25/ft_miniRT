/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_miscellaneous.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:24:24 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/17 11:05:51 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_reset_impact(t_impact *impact)
{
	impact->intersect = 0;
	impact->near = INFINITY;
	impact->normal = (t_vector){0};
}

int	key_hook(int keycode, t_mlx *window)
{
   if (keycode == ESC)
	   exit(1);
	if (keycode == 65307)
		exit(1);
   return (0);
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->address + (y * img->line_len + x * (img->bpp / 8));
	*(unsigned int *)dst = color;
}

t_vector	ft_copy_vector(t_vector copy)
{
	t_vector	new;

	new.x = copy.x;
	new.y = copy.y;
	new.z = copy.z;
	return (new);
}

t_vector	ft_new_vector(double x, double y, double z)
{
	t_vector	new;

	new.x = x;
	new.y = y;
	new.z = z;
	return (new);
}
