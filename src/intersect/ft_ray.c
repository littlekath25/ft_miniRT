/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ray.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:15:19 by katherine     #+#    #+#                 */
/*   Updated: 2021/03/29 15:20:56 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static t_vector	ft_get_direction(int w, int h, t_vector dir, t_camera *camera, t_scene *scene)
{
	double	ratio;
	double	fov;

	fov = tan((double)camera->fov / 2 * M_PI / 180);
	ratio = (double)scene->width / scene->height;
	dir.x = ((double)w / scene->width) - camera->pos.x - 0.5;
	dir.y = ((double)h / scene->height) - camera->pos.y - 0.5;
	dir.z = (fov - camera->pos.z) * camera->ori.z;
	dir.x *= ratio;
	ft_normalize(&dir);
	return (dir);
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
