/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   shade.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:08:46 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/28 15:49:56 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_colors	get_color(t_impact *impact, \
t_light *light, t_colors final_rgb)
{
	t_colors	light_color;
	t_vector	object_normal;
	t_vector	light_dir;
	double		dot;

	object_normal = impact->normal;
	light_dir = subtract(light->pos, impact->hitpoint);
	normalize(&object_normal);
	normalize(&light_dir);
	dot = dot_product(object_normal, light_dir);
	if (dot < 0)
		dot = 0;
	light_color = color_scale(light->colors, light->ratio * dot);
	final_rgb = color_add(final_rgb, color_mult(impact->rgb, light_color));
	return (final_rgb);
}

t_colors	check_lights(t_impact *impact, t_ray *shadow_ray, \
t_impact *shadow_impact, t_list *light_ptr)
{
	t_colors	final_rgb;
	t_scene		*scene;

	scene = static_scene();
	final_rgb = color_mult(impact->rgb, scene->ambient.colors);
	while (light_ptr != NULL)
	{
		shadow_ray = create_ray(shadow_ray, \
		impact->hitpoint, ((t_light *)(light_ptr->content))->pos);
		if (check_intersect(shadow_ray, shadow_impact, scene) && \
		shadow_impact->near < shadow_ray->len)
		{
			light_ptr = light_ptr->next;
			free(shadow_ray);
			continue ;
		}
		else
			final_rgb = get_color(impact, \
			(t_light *)light_ptr->content, final_rgb);
		light_ptr = light_ptr->next;
		free(shadow_ray);
	}
	free(shadow_impact);
	return (final_rgb);
}

int	shade_object(t_impact *impact, t_scene *scene)
{
	unsigned int	final;
	t_colors		final_rgb;
	t_list			*light_ptr;
	t_ray			*shadow_ray;
	t_impact		*shadow_impact;

	light_ptr = (t_list *)scene->light;
	shadow_impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	shadow_ray = NULL;
	if (shadow_impact == NULL)
		error_and_exit(3, "Shadow impact - ");
	reset_impact(shadow_impact);
	final_rgb = check_lights(impact, shadow_ray, shadow_impact, light_ptr);
	final = create_trgb(1, final_rgb.r, final_rgb.g, final_rgb.b);
	return (final);
}
