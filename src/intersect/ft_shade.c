/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/14 18:18:46 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static	t_colors ft_shadow_color(t_impact *impact, t_scene *scene)
{
	t_colors	final_color;

	final_color = ft_color_mult(impact->rgb, scene->ambient.colors);
	return (final_color);
}

static t_colors	ft_get_color(t_impact *impact, t_scene *scene, t_light *light)
{
	t_colors	final_color;
	t_colors	light_color;
	t_vector	object_normal;
	t_vector	light_dir;
	double		dot;

	final_color = ft_color_mult(impact->rgb, scene->ambient.colors);
	object_normal = impact->normal;
	light_dir = ft_subtract(light->pos, impact->hitpoint);
	ft_normalize(&object_normal);
	ft_normalize(&light_dir);
	dot = ft_dot_product(object_normal, light_dir);
	if (dot < 0)
		dot = 0;
	light_color = ft_color_scale(light->colors, light->ratio * dot);
	final_color = ft_color_add(final_color, ft_color_mult(impact->rgb, light_color));
	return (final_color);
}	

int     ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene)
{
	unsigned	final;
	t_colors	final_rgb;
	t_list		*light_ptr;
	t_ray		*shadow_ray;
	t_impact	*shadow_impact;

	light_ptr = (t_list *)scene->light;
	shadow_impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	shadow_ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	ft_reset_impact(shadow_impact);
	while (light_ptr != NULL)
	{
		shadow_ray = ft_create_ray(shadow_ray, impact->hitpoint, ((t_light *)(light_ptr->content))->pos);
		if(ft_check_intersect(shadow_ray, shadow_impact, scene) && shadow_impact->near < shadow_ray->len)
			final_rgb = ft_shadow_color(impact, scene);
		else
			final_rgb = ft_get_color(impact, scene, (t_light *)light_ptr->content);
		light_ptr = light_ptr->next;
	}
	final = ft_create_trgb(1, final_rgb.r, final_rgb.g, final_rgb.b);
	return (final);
}
