/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_color.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:28:17 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/03 11:28:31 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

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
