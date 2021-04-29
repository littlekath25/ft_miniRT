/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   triangle.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 19:47:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/27 20:51:29 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	solve(t_ray *ray, t_triangle *triangle)
{
	static t_solve_triangle	info;

	info.e1 = subtract(triangle->pos2, triangle->pos1);
	info.e2 = subtract(triangle->pos3, triangle->pos1);
	info.p = cross_product(ray->dir, info.e2);
	info.d = dot_product(info.e1, info.p);
	if (fabs(info.d) < RAY_MIN)
		return (INFINITY);
	info.d = 1 / info.d;
	info.t = subtract(ray->pos, triangle->pos1);
	info.u = dot_product(info.t, info.p) * info.d;
	if (info.u < 0 || info.u > 1)
		return (INFINITY);
	info.q = cross_product(info.t, info.e1);
	info.v = dot_product(ray->dir, info.q) * info.d;
	if (info.v < 0 || info.u + info.v > 1)
		return (INFINITY);
	info.t_near = dot_product(info.e2, info.q) * info.d;
	return (info.t_near);
}

void	intersect_triangle(t_ray *ray, t_impact *impact, t_triangle *triangle)
{
	double		t_near;
	double		dot;
	t_vector	ori;

	t_near = solve(ray, triangle);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = triangle->colors;
		impact->hitpoint = hitpoint(ray->pos, ray->dir, impact->near);
		ori = cross_product(subtract(triangle->pos2, triangle->pos1), \
		subtract(triangle->pos3, triangle->pos1));
		dot = dot_product(ori, ray->dir);
		if (dot < 0)
			impact->normal = ori;
		else
			impact->normal = scale(ori, -1);
		impact->hitpoint = hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
