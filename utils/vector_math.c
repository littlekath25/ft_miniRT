/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/16 22:25:47 by katherine     #+#    #+#                 */
/*   Updated: 2021/03/29 12:06:50 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void ft_normalize(t_vector *vec)
{
    double w;
	
	w = ft_magnitude(*vec);
    vec->x /= w;
    vec->y /= w;
    vec->z /= w;
}

double		ft_magnitude(t_vector vector)
{
	return (sqrt(pow(vector.x, 2) + pow(vector.y, 2) + pow(vector.z, 2)));
}

t_vector	ft_cross_product(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.y * v2.z - v1.z * v2.y;
	new.y = v1.z * v2.x - v1.x * v2.z;
	new.z = v1.x * v2.y - v1.y * v2.x;
	return (new);
}

double	ft_dot_product(t_vector v1, t_vector v2)
{
	return ((v1.x * v2.x) + (v1.y * v2.y) + (v1.z * v2.z));
}
