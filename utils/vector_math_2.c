/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math_2.c                                    :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:05:00 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/02 16:43:06 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	ft_hitpoint(t_vector v1, t_vector v2, double t)
{
	t_vector new;
	
	new.x = v1.x + v2.x * t;
	new.y = v1.y + v2.y * t;
	new.z = v1.z + v2.z * t;
	return (new);
}

t_vector	ft_add(t_vector v1, t_vector v2)
{
	t_vector	new;
	
	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector	ft_subtract(t_vector v1, t_vector v2)
{
	t_vector	new;
	
	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vector	ft_scale(t_vector v1, double scalar)
{
	t_vector	new;
	
	new.x = v1.x * scalar;
	new.y = v1.y * scalar;
	new.z = v1.z * scalar;
	return (new);
}
