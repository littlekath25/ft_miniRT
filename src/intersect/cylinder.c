/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   cylinder.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 22:26:31 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/29 20:07:51 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static void	get_normal(t_ray *ray, \
t_impact *new_impact, double t_near)
{
	ray->dir.x *= t_near;
	ray->dir.y *= t_near;
	ray->dir.z *= t_near;
	new_impact->hitpoint = add(ray->pos, ray->dir);
	normalize(&ray->dir);
}

static double	find_edges(t_cylinder *cylinder, \
t_ray *ray, t_impact *new_impact, t_solve_cylinder *info)
{
	double	max;

	get_normal(ray, new_impact, info->t_near);
	max = sqrt(pow(cylinder->height / 2.0, 2) + pow(cylinder->diameter, 2));
	if (magnitude(subtract(new_impact->hitpoint, cylinder->pos)) > max)
	{
		info->t_near = info->t_2;
		get_normal(ray, new_impact, info->t_near);
	}
	if (magnitude(subtract(new_impact->hitpoint, cylinder->pos)) > max)
		return (INFINITY);
	return (info->t_near);
}

static double	solve(t_ray *ray, t_impact *impact, t_cylinder *cylinder)
{
	t_solve_cylinder	info;
	t_ray				new_r;
	t_vector			r_o;
	t_impact			new_i;

	new_i = *impact;
	new_r.pos = ray->pos;
	new_r.dir = cross_product(ray->dir, cylinder->ori);
	r_o = subtract(ray->pos, cylinder->pos);
	info.quad.a = dot_product(new_r.dir, new_r.dir);
	info.quad.b = 2 * dot_product(new_r.dir, cross_product(r_o, cylinder->ori));
	info.quad.c = dot_product(cross_product(r_o, cylinder->ori), \
	cross_product(r_o, cylinder->ori)) - pow(cylinder->diameter, 2);
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
	return (find_edges(cylinder, ray, &new_i, &info));
}

void	intersect_cylinder(t_ray *ray, \
t_impact *impact, t_cylinder *cylinder)
{
	double		t_near;
	double		a;

	t_near = solve(ray, impact, cylinder);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = cylinder->colors;
		impact->hitpoint = hitpoint(ray->pos, ray->dir, impact->near);
		a = dot_product(cylinder->ori, \
		subtract(impact->hitpoint, cylinder->pos));
		impact->normal = subtract(impact->hitpoint, \
		add(cylinder->pos, scale(cylinder->ori, a)));
		normalize(&impact->normal);
		a = dot_product(ray->dir, impact->normal);
		if (a > 0)
			impact->normal = scale(impact->normal, -1);
		impact->hitpoint = hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
