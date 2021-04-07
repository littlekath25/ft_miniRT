/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_triangle.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 19:47:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/07 21:17:05 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_sphere.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/19 11:07:18 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/07 19:46:34 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double		ft_solve(t_ray *ray, t_impact *impact, t_camera *camera, t_triangle *triangle)
{
	t_vector	e1; 
	t_vector	e2;
	t_vector	p;
	t_vector	t;
	t_vector	q;
	double		d;
	double		t_near;
	double		u;
	double		v;

	e1 = ft_subtract(triangle->pos2, triangle->pos1);
	e2 = ft_subtract(triangle->pos3, triangle->pos1);
	p = ft_cross_product(ray->dir, e2);
	d = ft_dot_product(e1, p);
	if (fabs(d) < RAY_MIN)
		return (INFINITY);
	d = 1 / d;
	t = ft_subtract(ray->pos, triangle->pos1);
	u = ft_dot_product(t, p) * d;
	if (u < 0 || u > 1)
		return (INFINITY);
	q  = ft_cross_product(t, e1);
	v = ft_dot_product(ray->dir, q) * d;
	if (v < 0 || u + v > 1)
		return (INFINITY);
	t_near = ft_dot_product(e2, q) * d;
	return (t_near);
}

void		ft_intersect_triangle(t_ray *ray, t_impact *impact, t_camera *camera, t_triangle *triangle)
{
	double		t_near;

	t_near = ft_solve(ray, impact, camera, triangle);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = triangle->colors;
		impact->normal = ft_cross_product(ft_subtract(triangle->pos2, triangle->pos1), ft_subtract(triangle->pos3, triangle->pos1));
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		impact->hitpoint = ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
