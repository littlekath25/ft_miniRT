/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 12:26:03 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/02 13:35:54 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_impact	*ft_check_intersect(t_ray *ray, t_impact *impact, t_camera *camera, t_scene *scene)
{
	t_list		*obj_ptr;

	obj_ptr = scene->objects;
	impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	impact->near = INFINITY;
	while (obj_ptr)
	{
		if (*((t_obj *)(obj_ptr)->content) == SP)
			ft_intersect_sphere(ray, impact, camera, (t_sphere *)obj_ptr->content);
		obj_ptr = obj_ptr->next;
	}
	if (impact->intersect == 1)
		impact->color = ft_shade_object(ray, impact, scene);
	return (impact);
}

void	ft_make_image(t_img *img, t_scene *scene)
{
	t_ray		*ray;
	t_impact	*impact;
	t_camera	*camera;
	int			width;
	int			height;

	width = 0;
	height = 0;
	impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	camera = (t_camera *)scene->camera->content;
	while (height < scene->height)
	{
		width = 0;
		while (width < scene->width)
		{
			ray = ft_generate_ray(ray, width, height, scene);
			impact = ft_check_intersect(ray, impact, camera, scene);
			my_mlx_pixel_put(img, width, height, impact->color);
			width++;
		}
		height++;
	}
}
