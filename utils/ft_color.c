/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_color.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 11:28:17 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/17 11:44:01 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

unsigned	ft_create_trgb(unsigned t, unsigned r, unsigned g, unsigned b)
{
	return (t << 24 | r << 16 | g << 8 | b);
}

t_colors	ft_color_add(t_colors color1, t_colors color2)
{
	t_colors new;
	
	new.r = color1.r + color2.r;
	new.g = color1.g + color2.g;
	new.b = color1.b + color2.b;
	if (new.r > 255)
		new.r = 255;
	if (new.g > 255)
		new.g = 255;
	if (new.b > 255)
		new.b = 255;
	return (new);
}

t_colors	ft_color_scale(t_colors color1, float ratio)
{
	t_colors new;
	
	new.r = color1.r * ratio;
	new.g = color1.g * ratio;
	new.b = color1.b * ratio;
	return (new);
}

t_colors	ft_color_mult(t_colors color1, t_colors color2)
{
	t_colors new;
	
	new.r = color1.r * color2.r / 255;
	new.g = color1.g * color2.g / 255;
	new.b = color1.b * color2.b / 255;
	return (new);
}
