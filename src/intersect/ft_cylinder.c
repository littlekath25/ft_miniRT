/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_cylinder->c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/07 19:47:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/11 18:24:15 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	get_norm(t_vector vect)
{
	return (sqrt(ft_dot_product(vect, vect)));
}

static void		ft_get_normal(t_ray *ray, t_vector obj_pos, t_impact *impact, double t_near)
{
	ray->dir.x *= t_near;
	ray->dir.y *= t_near;
	ray->dir.z *= t_near;
	impact->hitpoint = ft_add(ray->pos, ray->dir);
	impact->normal = (ft_subtract(impact->hitpoint, obj_pos));
	ft_normalize(&impact->normal);
}

static double	ft_find_edges(t_cylinder *cylinder, t_ray *ray, t_impact *impact, double t_near, double t1, double t2)
{
	double a;
	double max;

	ft_get_normal(ray, cylinder->pos, impact, t_near);
	max = sqrt(pow(cylinder->height / 2.0, 2) + pow(cylinder->diameter / 2, 2));
	if (get_norm(ft_subtract(impact->hitpoint, cylinder->pos)) > max)
	{
		t_near = t2;
		ft_get_normal(ray, cylinder->pos, impact, t_near);
	}
	if (get_norm(ft_subtract(impact->hitpoint, cylinder->pos)) > max)
		return (INFINITY);
	a = ft_dot_product(cylinder->normal, ft_subtract(impact->hitpoint, cylinder->pos));
	impact->normal = ft_subtract(impact->hitpoint, ft_add(cylinder->pos, ft_scale(cylinder->normal, a)));
	ft_normalize(&impact->normal);
	a = ft_dot_product(ray->dir, impact->normal);
	if (a > 0)
		impact->normal = ft_scale(impact->normal, -1);
	return (t_near);
}

static double	ft_solve(t_ray *ray, t_impact *impact, t_cylinder *cylinder)
{
	t_quad          quad;
	t_ray			new_ray;
	t_vector		ray_object;
	double			t_near;
	double			t_1;
	double			t_2;

	new_ray.pos = ray->pos;
	new_ray.dir = ft_cross_product(ray->dir, cylinder->normal);
	ray_object = ft_subtract(ray->pos, cylinder->pos);
	quad.a = ft_dot_product(new_ray.dir, new_ray.dir);
	quad.b = 2 * ft_dot_product(new_ray.dir, ft_cross_product(ray_object, cylinder->normal));
	quad.c = ft_dot_product(ft_cross_product(ray_object, cylinder->normal),
		ft_cross_product(ray_object, cylinder->normal)) - pow(cylinder->diameter, 2);
	quad.disc = pow(quad.b, 2) - 4 * quad.c * quad.a;
	if (quad.disc < 0)
		return (INFINITY);
	t_1 = (-quad.b - sqrt(quad.disc)) / (2 * quad.a);
	t_2 = (-quad.b + sqrt(quad.disc)) / (2 * quad.a);
	if (t_2 < 0)
		return (INFINITY);
	if (t_1 > 0)
		t_near = t_1;
	else
		t_near = t_2;
    return (ft_find_edges(cylinder, ray, impact, t_near, t_1, t_2));
}

void		ft_intersect_cylinder(t_ray *ray, t_impact *impact, t_cylinder *cylinder)
{
	double		t_near;

	t_near = ft_solve(ray, impact, cylinder);
	if (t_near < impact->near && t_near > RAY_MIN)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = cylinder->colors;
		impact->normal = ft_subtract(impact->hitpoint, cylinder->pos);
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		impact->hitpoint = ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
