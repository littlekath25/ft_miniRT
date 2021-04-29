/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ray.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 14:15:19 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/28 18:24:01 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	transform(t_vector pixel, t_matrix matrix)
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

t_matrix	camera_rotation(t_camera *camera)
{
	t_vector	tmp;
	t_matrix	matrix;

	tmp = new_vector(0, 1, 0);
	matrix.forward = camera->ori;
	matrix.right = cross_product(tmp, matrix.forward);
	if (matrix.right.x == 0 && matrix.right.y == 0 && matrix.right.z == 0)
		matrix.right = new_vector(1, 0, 0);
	matrix.up = cross_product(matrix.forward, matrix.right);
	matrix.origin = camera->pos;
	matrix.x = 0;
	matrix.y = 0;
	matrix.z = 0;
	matrix.w = 1;
	return (matrix);
}

t_ray	*create_ray(t_ray *ray, t_vector hitpoint, t_vector light)
{
	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	if (ray == NULL)
		error_and_exit(3, "Ray struct - ");
	ray->pos = hitpoint;
	ray->dir = subtract(light, hitpoint);
	ray->len = magnitude(ray->dir);
	normalize(&ray->dir);
	return (ray);
}

t_ray	*generate_ray(t_ray *ray, double w, double h, t_scene *scene)
{
	t_camera	*camera;
	t_matrix	matrix;

	camera = (t_camera *)scene->current_cam->content;
	matrix = camera_rotation(camera);
	camera->length = scene->width / 2 / camera->fov;
	w = w - (scene->width / 2) - camera->pos.x - 0.5;
	h = scene->height / 2 - h - camera->pos.y - 0.5;
	ray->dir = transform(new_vector(w, h, camera->length), matrix);
	normalize(&ray->dir);
	ray->pos = camera->pos;
	ray->len = INFINITY;
	return (ray);
}
