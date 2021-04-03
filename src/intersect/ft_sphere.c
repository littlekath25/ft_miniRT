/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 11:07:18 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/03 17:18:24 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static int		ft_solve_quadratic(double a, double b, double c, t_impact *impact)
{
	double	disc;
	double	t_near;
	double  second;

	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (0);
	if (disc == 0)
		t_near = -b / (2 * a);
	if (disc > 0)
	{
		t_near = (-b  + sqrt(disc)) / (2 * a);
		second = (-b  - sqrt(disc)) / (2 * a);
		if (second < t_near && second > RAY_MIN)
			t_near = second;
	}
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->near = t_near;
		return (1);
	}
	return (0);
}

void		ft_intersect_sphere(t_ray *ray, t_impact *impact, t_camera *camera, t_sphere *object)
{
	double		a;
	double		b;
	double		c;
	t_vector	len;

	len = ft_subtract(camera->pos, object->pos);
	a = ft_dot_product(ray->dir, ray->dir);
	b = 2 * ft_dot_product(ray->dir, len);
	c = ft_dot_product(len, len) - pow(object->diameter, 2);
	if (ft_solve_quadratic(a, b, c, impact))
	{
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		impact->rgb = object->colors;
		impact->object_pos = object->pos;
		impact->intersect = 1;
	}
}
