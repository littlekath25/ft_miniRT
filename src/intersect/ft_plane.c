/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_plane.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/03 12:23:53 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/03 18:40:23 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void		ft_intersect_plane(t_ray *ray, t_impact *impact, t_camera *camera, t_plane *object)
{
	double		denom;
	double		t_near;
	t_vector	ray_object;

	denom = -ft_dot_product(object->ori, ray->dir);
	if (fabs(denom) > 0) {
		ray_object = ft_subtract(object->pos, ray->pos);
		t_near = -ft_dot_product(ray_object, object->ori) / denom;
		if (t_near > 1e-4 && t_near < impact->near)
		{
			impact->near = t_near;
			impact->hitpoint = ft_hitpoint(ray->pos, ray->dir, impact->near);
			impact->rgb = object->colors;
			impact->object_pos = object->pos;
			impact->intersect = 1;
		}
	}
}
