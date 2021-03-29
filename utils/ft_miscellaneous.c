/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_miscellaneous.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/08 17:24:24 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/29 14:05:25 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_create_trgb(int t, int r, int g, int b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

int	key_hook(int keycode, t_mlx *window)
{
   if (keycode == 65307)
	   exit(1);
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
