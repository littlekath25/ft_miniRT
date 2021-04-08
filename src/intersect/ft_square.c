/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_square->c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/08 11:04:10 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/08 11:51:08 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

static double	ft_solve(t_ray *ray, t_impact *impact, t_square *square)
{
	double		denom;
	t_vector	hit_point;
	t_vector	ray_sq;
	double		t_near;

	denom = ft_dot_product(square->normal, ray->dir);
	if (fabs(denom) > RAY_MIN)
	{
		ray_sq = ft_subtract(square->pos, ray->pos);
		t_near = ft_dot_product(ray_sq, square->normal) / denom;
		hit_point = ft_add(ray->pos, ft_scale(ray->dir, t_near));
		if (t_near >= 0)
		{
			if (fabs(hit_point.x - square->pos.x) > (square->side / 2))
				return (INFINITY);
			if (fabs(hit_point.y - square->pos.y) > (square->side/ 2))
				return (INFINITY);
			if (fabs(hit_point.z - square->pos.z) > (square->side / 2))
				return (INFINITY);
			else
				return (t_near);
		}
		else
			return (INFINITY);
	}
}

void		ft_intersect_square(t_ray *ray, t_impact *impact, t_square *square)
{
	double  t_near;

	t_near = ft_solve(ray, impact, square);
	if (t_near > RAY_MIN && t_near < impact->near)
	{
		impact->intersect = 1;
		impact->near = t_near;
		impact->normal = square->normal;
		impact->rgb = square->colors;
		impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
		impact->hitpoint = ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
	}
}