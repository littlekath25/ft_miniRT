/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ray.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:15:19 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/14 13:58:44 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_vector	ft_get_direction(int w, int h, t_vector dir, t_camera *camera, t_scene *scene)
{
	double	fov;

	fov = (scene->width / 2) / (camera->fov * (M_PI / 180));
	dir.x = ((double)w - (scene->width / 2)) - camera->pos.x - 0.5;
	dir.y = ((double)scene->height / 2 - h) - camera->pos.y - 0.5;
	dir.z = fov - camera->pos.z;
	ft_normalize(&dir);
	return (dir);
}

t_ray	*ft_create_ray(t_ray *ray, t_vector hitpoint, t_vector light)
{
	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	ray->pos = hitpoint;
	ray->dir = ft_subtract(light, hitpoint);
	ray->len = ft_magnitude(ray->dir);
	ft_normalize(&ray->dir);
	return (ray);
}

t_ray	*ft_generate_ray(t_ray *ray, int w, int h, t_scene *scene)
{
	t_camera *camera;

	camera = (t_camera *)scene->camera->content;
	ray->dir = ft_get_direction(w, h, ray->dir, camera, scene);
	ray->pos = camera->pos;
	ray->len = INFINITY;
	return (ray);
}
