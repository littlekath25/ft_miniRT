/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cylinder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 22:26:31 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/27 21:02:29 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	ft_get_normal(t_ray *ray, \
t_impact *new_impact, double t_near)
{
	ray->dir.x *= t_near;
	ray->dir.y *= t_near;
	ray->dir.z *= t_near;
	new_impact->hitpoint = ft_add(ray->pos, ray->dir);
	ft_normalize(&ray->dir);
}

static double	ft_find_edges(t_cylinder *cylinder, \
t_ray *ray, t_impact *new_impact, t_solve_cylinder *info)
{
	double	max;

	ft_get_normal(ray, new_impact, info->t_near);
	max = sqrt(pow(cylinder->height / 2.0, 2) + pow(cylinder->diameter, 2));
	if (ft_magnitude(ft_subtract(new_impact->hitpoint, cylinder->pos)) > max)
	{
		info->t_near = info->t_2;
		ft_get_normal(ray, new_impact, info->t_near);
	}
	if (ft_magnitude(ft_subtract(new_impact->hitpoint, cylinder->pos)) > max)
		return (INFINITY);
	return (info->t_near);
}

static double	ft_solve(t_ray *ray, t_impact *impact, t_cylinder *cylinder)
{
	t_solve_cylinder	info;
	t_ray				new_ray;
	t_vector			ray_object;
	t_impact			new_impact;

	new_impact = *impact;
	new_ray.pos = ray->pos;
	new_ray.dir = ft_cross_product(ray->dir, cylinder->ori);
	ray_object = ft_subtract(ray->pos, cylinder->pos);
	info.quad.a = ft_dot_product(new_ray.dir, new_ray.dir);
	info.quad.b = 2 * ft_dot_product(new_ray.dir, \
	ft_cross_product(ray_object, cylinder->ori));
	info.quad.c = ft_dot_product(ft_cross_product(ray_object, cylinder->ori), \
	ft_cross_product(ray_object, cylinder->ori)) - pow(cylinder->diameter, 2);
	info.quad.disc = pow(info.quad.b, 2) - 4 * info.quad.c * info.quad.a;
	if (info.quad.disc < 0)
		return (INFINITY);
	info.t_1 = (-info.quad.b - sqrt(info.quad.disc)) / (2 * info.quad.a);
	info.t_2 = (-info.quad.b + sqrt(info.quad.disc)) / (2 * info.quad.a);
	if (info.t_2 < 0)
		return (INFINITY);
	if (info.t_1 > 0)
		info.t_near = info.t_1;
	else
		info.t_near = info.t_2;
	return (ft_find_edges(cylinder, ray, &new_impact, &info));
}

void	ft_intersect_cylinder(t_ray *ray, \
t_impact *impact, t_cylinder *cylinder)
{
	double		t_near;
	double		a;

	t_near = ft_solve(ray, impact, cylinder);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = cylinder->colors;
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		a = ft_dot_product(cylinder->ori, \
		ft_subtract(impact->hitpoint, cylinder->pos));
		impact->normal = ft_subtract(impact->hitpoint, \
		ft_add(cylinder->pos, ft_scale(cylinder->ori, a)));
		ft_normalize(&impact->normal);
		a = ft_dot_product(ray->dir, impact->normal);
		if (a > 0)
			impact->normal = ft_scale(impact->normal, -1);
		impact->hitpoint = \
		ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
