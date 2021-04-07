/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/07 19:31:14 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_colors	ft_get_color(t_impact *impact, t_scene *scene, t_light *light, t_colors colors)
{
	t_colors	tmp;
	t_colors	light_color;
	t_vector	object_normal;
	t_vector	light_dir;
	double		dot;
	
	tmp = ft_color_mult(impact->rgb, scene->ambient.colors);
	object_normal = impact->normal;
	light_dir = ft_subtract(light->pos, impact->hitpoint);
	ft_normalize(&object_normal);
	ft_normalize(&light_dir);
	dot = ft_dot_product(object_normal, light_dir);
	if (dot < 0)
		dot = 0;
	light_color = ft_color_amb(light->colors, light->ratio * dot);
	tmp = ft_color_add(tmp, ft_color_mult(impact->rgb, light_color));
	colors = ft_color_add(colors, tmp);
	return (colors);
}	

int		ft_shadow_ray()
{
	
}

int     ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene)
{
	t_colors	colors;
	unsigned	final;
	t_list		*light_ptr;

	light_ptr = (t_list *)scene->light;
	while (light_ptr != NULL)
	{
		// if (ft_shadow_ray())
		// 	printf("SHADOW!\n");
		// else
		colors = ft_get_color(impact, scene, (t_light *)light_ptr->content, colors);
		light_ptr = light_ptr->next;
	}
	final = ft_create_trgb(1, colors.r, colors.g, colors.b);
	return (final);
}
