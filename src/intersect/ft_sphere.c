/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 11:07:18 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/08 12:23:39 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double		ft_solve(t_ray *ray, t_impact *impact, t_sphere *sphere)
{
	double		disc;
	double		second;
	double		t_near;
	double		a;
	double		b;
	double		c;
	t_vector	len;

	len = ft_subtract(ray->pos, sphere->pos);
	a = ft_dot_product(ray->dir, ray->dir);
	b = 2 * ft_dot_product(ray->dir, len);
	c = ft_dot_product(len, len) - pow(sphere->diameter, 2);
	disc = b * b - 4 * a * c;
	if (disc < 0)
		return (INFINITY);
	if (disc == 0)
		t_near = -b / (2 * a);
	if (disc > 0)
	{
		t_near = (-b  + sqrt(disc)) / (2 * a);
		second = (-b  - sqrt(disc)) / (2 * a);
		if (second < t_near && second > RAY_MIN)
			t_near = second;
	}
	return (t_near);
}

void		ft_intersect_sphere(t_ray *ray, t_impact *impact, t_sphere *sphere)
{
	double		t_near;

	t_near = ft_solve(ray, impact, sphere);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->normal = ft_subtract(impact->hitpoint, sphere->pos);
		impact->rgb = sphere->colors;
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		impact->hitpoint = ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
