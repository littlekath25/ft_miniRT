/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 12:23:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/08 12:29:19 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_intersect_plane(t_ray *ray, t_impact *impact, t_plane *plane)
{
	double		denom;
	double		t_near;
	t_vector	ray_object;

	denom = ft_dot_product(plane->normal, ray->dir);
	if (fabs(denom) > 0)
	{
		ray_object = ft_subtract(plane->pos, ray->pos);
		t_near = ft_dot_product(ray_object, plane->normal) / denom;
		if (t_near > RAY_MIN && t_near < impact->near)
		{
			impact->intersect = 1;
			impact->near = t_near;
			impact->normal = plane->normal;
			impact->rgb = plane->colors;
			impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
			impact->hitpoint = ft_hitpoint(impact->hitpoint, impact->normal, RAY_MIN);
		}
	}
}
