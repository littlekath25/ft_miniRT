/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 11:07:18 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/26 22:18:31 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	solve(t_ray *ray, t_sphere *sphere)
{
	t_quad		quad;
	double		second;
	double		t_near;
	t_vector	len;

	len = subtract(ray->pos, sphere->pos);
	quad.a = dot_product(ray->dir, ray->dir);
	quad.b = 2 * dot_product(ray->dir, len);
	quad.c = dot_product(len, len) - pow(sphere->diameter, 2);
	quad.disc = quad.b * quad.b - 4 * quad.a * quad.c;
	if (quad.disc < 0)
		return (INFINITY);
	if (quad.disc == 0)
		t_near = -quad.b / (2 * quad.a);
	if (quad.disc > 0)
	{
		t_near = (-quad.b + sqrt(quad.disc)) / (2 * quad.a);
		second = (-quad.b - sqrt(quad.disc)) / (2 * quad.a);
		if (second < t_near && second > RAY_MIN)
			t_near = second;
	}
	return (t_near);
}

void	intersect_sphere(t_ray *ray, t_impact *impact, t_sphere *sphere)
{
	double		t_near;

	t_near = solve(ray, sphere);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = sphere->colors;
		impact->hitpoint = hitpoint(ray->pos, ray->dir, impact->near);
		impact->normal = subtract(impact->hitpoint, sphere->pos);
		impact->hitpoint = hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
