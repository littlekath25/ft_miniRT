/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 12:26:03 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/28 15:46:04 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_intersect(t_ray *ray, t_impact *impact, t_scene *scene)
{
	t_list		*obj_ptr;

	obj_ptr = scene->objects;
	reset_impact(impact);
	while (obj_ptr)
	{
		if (*((t_obj *)(obj_ptr)->content) == SP)
			intersect_sphere(ray, impact, (t_sphere *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == PL)
			intersect_plane(ray, impact, (t_plane *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == TR)
			intersect_triangle(ray, impact, (t_triangle *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == SQ)
			intersect_square(ray, impact, (t_square *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == CY)
			intersect_cylinder(ray, impact, (t_cylinder *)obj_ptr->content);
		obj_ptr = obj_ptr->next;
	}
	if (impact->intersect == 1)
		return (1);
	return (0);
}

void	shoot_ray(t_img *img, t_ray *ray, t_impact *impact, t_scene *scene)
{
	int	height;
	int	width;
	int	color;

	height = 0;
	while (height < scene->height)
	{
		width = 0;
		while (width < scene->width)
		{
			color = 0;
			ray = generate_ray(ray, width, height, scene);
			if (check_intersect(ray, impact, scene))
				color = shade_object(impact, scene);
			my_mlx_pixel_put(img, width, height, color);
			width++;
		}
		height++;
	}
}

void	make_image(t_img *img, t_scene *scene)
{
	t_ray		*ray;
	t_impact	*impact;

	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (ray == NULL)
		error_and_exit(3, "Ray struct - ");
	impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	if (impact == NULL)
		error_and_exit(3, "Impact struct - ");
	shoot_ray(img, ray, impact, scene);
	free(impact);
	free(ray);
}
