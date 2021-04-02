/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/02 16:55:23 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_colors	ft_color_add(t_colors color1, t_colors color2)
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

static t_colors	ft_color_amb(t_colors color1, float ratio)
{
	color1.r = color1.r * ratio;
	color1.g = color1.g * ratio;
	color1.b = color1.b * ratio;
	return (color1);
}

static t_colors	ft_color_mult(t_colors color1, t_colors color2)
{
	color1.r = color1.r * color2.r / 255;
	color1.g = color1.g * color2.g / 255;
	color1.b = color1.b * color2.b / 255;
	return (color1);
}

int     ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene)
{
	int			final;
	t_colors	color;
	t_colors	lightcolor;
	t_colors	ambient;
	t_vector	norm;
	t_vector	light;
	t_light		*light_ptr;
	double		dot;

	ambient = ft_color_amb(scene->ambient.colors, scene->ambient.ratio);
	color = ft_color_mult(impact->rgb, ambient);
	light_ptr = (t_light *)scene->light->content;
	norm = ft_subtract(impact->hitpoint, impact->object_pos);
	light = ft_subtract(light_ptr->pos, impact->hitpoint);
	ft_normalize(&norm);
	ft_normalize(&light);
	dot = ft_dot_product(norm, light);
	if (dot < 0)
		dot = 0;
	lightcolor = ft_color_amb(light_ptr->colors, light_ptr->ratio * dot);
	color = ft_color_add(color, ft_color_mult(impact->rgb, lightcolor));
	final = ft_create_trgb(1, color.r, color.g, color.b);
	return (final);
}
