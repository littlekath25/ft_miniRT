/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   square.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/26 22:28:27 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/26 22:28:29 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	solve(t_ray *ray, t_square *square)
{
	double		denom;
	t_vector	hit_point;
	t_vector	ray_object;
	double		t_near;

	denom = dot_product(square->ori, ray->dir);
	if (fabs(denom) > RAY_MIN)
	{
		ray_object = subtract(square->pos, ray->pos);
		t_near = dot_product(ray_object, square->ori) / denom;
		hit_point = add(ray->pos, scale(ray->dir, t_near));
		if (t_near > RAY_MIN)
		{
			if (fabs(hit_point.x - square->pos.x) > (square->side / 2))
				return (INFINITY);
			if (fabs(hit_point.y - square->pos.y) > (square->side / 2))
				return (INFINITY);
			if (fabs(hit_point.z - square->pos.z) > (square->side / 2))
				return (INFINITY);
			return (t_near);
		}
	}
	return (INFINITY);
}

void	intersect_square(t_ray *ray, t_impact *impact, t_square *square)
{
	double	t_near;
	double	dot;

	t_near = solve(ray, square);
	if (t_near > RAY_MIN && t_near < impact->near && t_near != INFINITY)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->rgb = square->colors;
		impact->hitpoint = hitpoint(ray->pos, ray->dir, impact->near);
		impact->normal = square->ori;
		dot = dot_product(square->ori, ray->dir);
		if (dot < 0)
			impact->normal = square->ori;
		else
			impact->normal = scale(square->ori, -1);
		impact->hitpoint = hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}
