/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/03/29 16:57:07 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int     ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene)
{
	double		refl;
	int			color;
	t_light		*light;

	refl = 1.0;
	color = 0;
	light = (t_light *)scene->light->content;
	impact->hitpoint = ft_new_vector(light->pos.x + impact->near * ray->dir.x, light->pos.y + impact->near * ray->dir.y, light->pos.z + impact->near * ray->dir.z);
	impact->normal = ft_new_vector(impact->hitpoint.x - impact->object_pos.x, impact->hitpoint.y - impact->object_pos.y, impact->hitpoint.z - impact->object_pos.z);
	ft_normalize(&impact->normal);
	refl = -ft_dot_product(ray->dir, impact->normal);
	color = ft_create_trgb(1, impact->rgb.r * refl, impact->rgb.g * refl, impact->rgb.b * refl);
	return (color);
}
