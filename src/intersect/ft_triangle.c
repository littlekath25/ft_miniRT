/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_triangle.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 19:47:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/27 20:51:29 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_solve(t_ray *ray, t_triangle *triangle)
{
	static t_solve_triangle	info;

	info.e1 = ft_subtract(triangle->pos2, triangle->pos1);
	info.e2 = ft_subtract(triangle->pos3, triangle->pos1);
	info.p = ft_cross_product(ray->dir, info.e2);
	info.d = ft_dot_product(info.e1, info.p);
	if (fabs(info.d) < RAY_MIN)
		return (INFINITY);
	info.d = 1 / info.d;
	info.t = ft_subtract(ray->pos, triangle->pos1);
	info.u = ft_dot_product(info.t, info.p) * info.d;
	if (info.u < 0 || info.u > 1)
		return (INFINITY);
	info.q = ft_cross_product(info.t, info.e1);
	info.v = ft_dot_product(ray->dir, info.q) * info.d;
	if (info.v < 0 || info.u + info.v > 1)
		return (INFINITY);
	info.t_near = ft_dot_product(info.e2, info.q) * info.d;
	return (info.t_near);
}

void	ft_intersect_triangle(\
t_ray *ray, t_impact *impact, t_triangle *triangle)
{
	double		t_near;
	double		dot;
	t_vector	ori;

	t_near = ft_solve(ray, triangle);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = triangle->colors;
		impact->hitpoint = \
		ft_hitpoint(ray->pos, ray->dir, impact->near);
		ori = ft_cross_product(ft_subtract(triangle->pos2, triangle->pos1), \
		ft_subtract(triangle->pos3, triangle->pos1));
		dot = ft_dot_product(ori, ray->dir);
		if (dot < 0)
			impact->normal = ori;
		else
			impact->normal = ft_scale(ori, -1);
		impact->hitpoint = \
		ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
