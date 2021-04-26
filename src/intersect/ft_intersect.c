/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 12:26:03 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/26 22:19:15 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_check_intersect(t_ray *ray, t_impact *impact, t_scene *scene)
{
	t_list		*obj_ptr;

	obj_ptr = scene->objects;
	ft_reset_impact(impact);
	while (obj_ptr)
	{
		if (*((t_obj *)(obj_ptr)->content) == SP)
			ft_intersect_sphere(ray, impact, (t_sphere *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == PL)
			ft_intersect_plane(ray, impact, (t_plane *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == TR)
			ft_intersect_triangle(ray, impact, (t_triangle *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == SQ)
			ft_intersect_square(ray, impact, (t_square *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == CY)
			ft_intersect_cylinder(ray, impact, (t_cylinder *)obj_ptr->content);
		obj_ptr = obj_ptr->next;
	}
	if (impact->intersect == 1)
		return (1);
	return (0);
}

void	ft_make_image(t_img *img)
{
	t_ray		*ray;
	t_impact	*impact;
	t_scene		*scene;
	int			width;
	int			height;
	int			color;

	width = 0;
	height = 0;
	impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	scene = ft_static_scene();
	if (scene->camera)
	{
		while (height < scene->height)
		{
			width = 0;
			while (width < scene->width)
			{
				color = 0;
				ray = ft_generate_ray(ray, width, height, scene);
				if (ft_check_intersect(ray, impact, scene))
					color = ft_shade_object(ray, impact, scene);
				my_mlx_pixel_put(img, width, height, color);
				width++;
			}
			height++;
		}
	}
	free(impact);
	free(ray);
}
