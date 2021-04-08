/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_intersect.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/18 12:26:03 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/08 12:17:17 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int		ft_check_intersect(t_ray *ray, t_impact *impact, t_camera *camera, t_scene *scene)
{
	t_list		*obj_ptr;

	obj_ptr = scene->objects;
	impact->near = INFINITY;
	while (obj_ptr)
	{
		if (*((t_obj *)(obj_ptr)->content) == SP)
			ft_intersect_sphere(ray, impact, camera, (t_sphere *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == PL)
			ft_intersect_plane(ray, impact, camera, (t_plane *)obj_ptr->content);
		if (*((t_obj *)(obj_ptr)->content) == TR)
			ft_intersect_triangle(ray, impact, camera, (t_triangle *)obj_ptr->content);
		// if (*((t_obj *)(obj_ptr)->content) == SQ)
		// 	ft_intersect_square(ray, impact, camera, (t_square *)obj_ptr->content);
		obj_ptr = obj_ptr->next;
	}
	if (impact->intersect == 1)
		return (1);
	return (0);
}

void	ft_make_image(t_img *img, t_scene *scene)
{
	t_ray		*ray;
	t_impact	*impact;
	t_camera	*camera;
	int			width;
	int			height;
	int			color;

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
			if(ft_check_intersect(ray, impact, camera, scene))
			{
				color = ft_create_trgb(1, impact->rgb.r, impact->rgb.g, impact->rgb.b);
				my_mlx_pixel_put(img, width, height, color);
			}
			width++;
		}
		height++;
	}
}
