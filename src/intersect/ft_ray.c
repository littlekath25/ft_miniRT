/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_ray.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:15:19 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/20 16:55:18 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_transform(t_vector pixel, t_matrix matrix)
{
	t_vector	ret;
	double		tmp[4];
	int			i;

	i = 0;
	while (i < 4)
	{
		tmp[i] = pixel.x * matrix.map[0][i]
			+ pixel.y * matrix.map[1][i]
			+ pixel.z * matrix.map[2][i]
			+ matrix.map[3][i];
		i++;
	}
	ret.x = tmp[0] / tmp[3];
	ret.y = tmp[1] / tmp[3];
	ret.z = tmp[2] / tmp[3];
	return (ret);
}

t_matrix	ft_camera_rotation(t_camera *camera)
{
	t_vector	tmp;
	t_matrix	matrix;

	tmp = ft_new_vector(0, 1, 0);
	matrix.forward = camera->ori;
	matrix.right = ft_cross_product(tmp, matrix.forward);
	if (matrix.right.x == 0 && matrix.right.y == 0 && matrix.right.z == 0)
		matrix.right = ft_new_vector(1, 0, 0);
	matrix.up = ft_cross_product(matrix.forward, matrix.right);
	matrix.origin = camera->pos;
	matrix.x = 0;
	matrix.y = 0;
	matrix.z = 0;
	matrix.w = 1;
	return (matrix);
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

t_ray	*ft_generate_ray(t_ray *ray, double w, double h, t_scene *scene)
{
	t_camera	*camera;
	t_matrix	matrix;
	double		z;

	camera = (t_camera *)scene->current_cam->content;
	matrix = ft_camera_rotation(camera);
	camera->length = scene->width / 2 / camera->fov;
	w = w - (scene->width / 2) - camera->pos.x - 0.5;
	h = scene->height / 2 - h - camera->pos.y - 0.5;
	ray->dir = ft_transform(ft_new_vector(w, h, camera->length), matrix);
	ft_normalize(&ray->dir);
	ray->pos = camera->pos;
	ray->len = INFINITY;
	return (ray);
}
