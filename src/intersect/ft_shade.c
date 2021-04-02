/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/02 14:31:55 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int     ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene)
{
	int			color;
	t_vector	norm;
	t_vector	light;
	t_light		*light_ptr;
	double		dot;

	light_ptr = (t_light *)scene->light->content;
	norm = ft_subtract(impact->hitpoint, impact->object_pos);
	light = ft_subtract(light_ptr->pos, impact->object_pos);
	ft_normalize(&norm);
	ft_normalize(&light);
	dot = -ft_dot_product(norm, light);
	color = ft_create_trgb(light_ptr->ratio, impact->rgb.r * dot, impact->rgb.g * dot, impact->rgb.b * dot);
	return (color);
}
