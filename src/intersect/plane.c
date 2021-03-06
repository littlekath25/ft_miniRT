/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   plane.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 12:23:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/26 22:19:31 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	intersect_plane(t_ray *ray, t_impact *impact, t_plane *plane)
{
	double		denom;
	double		t_near;
	double		dot;
	t_vector	ray_object;

	denom = dot_product(plane->ori, ray->dir);
	if (fabs(denom) > 0)
	{
		ray_object = subtract(plane->pos, ray->pos);
		t_near = dot_product(ray_object, plane->ori) / denom;
		if (t_near > RAY_MIN && t_near < impact->near)
		{
			impact->intersect = 1;
			impact->near = t_near;
			impact->rgb = plane->colors;
			impact->hitpoint = hitpoint(ray->pos, ray->dir, impact->near);
			dot = dot_product(plane->ori, ray->dir);
			if (dot < 0)
				impact->normal = plane->ori;
			else
				impact->normal = scale(plane->ori, -1);
			impact->hitpoint = \
			hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
		}
	}
}
