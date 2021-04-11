/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_color.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:28:17 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/10 20:17:39 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned	ft_create_trgb(unsigned t, unsigned r, unsigned g, unsigned b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_colors	ft_reset_color(t_colors color)
{
	color.r = 0;
	color.g = 0;
	color.b = 0;
	return (color);
}

t_colors	ft_color_add(t_colors color1, t_colors color2)
{
	color1.r += color2.r;
	color1.g += color2.g;
	color1.b += color2.b;
	
	if (color1.r > 255)
		color1.r = 255;
	if (color1.g > 255)
		color1.g = 255;
	if (color1.b > 255)
		color1.b = 255;
	return (color1);
}

t_colors	ft_color_amb(t_colors color1, float ratio)
{
	color1.r = color1.r * ratio;
	color1.g = color1.g * ratio;
	color1.b = color1.b * ratio;
	return (color1);
}

t_colors	ft_color_mult(t_colors color1, t_colors color2)
{
	color1.r = color1.r * color2.r / 255;
	color1.g = color1.g * color2.g / 255;
	color1.b = color1.b * color2.b / 255;
	return (color1);
}
