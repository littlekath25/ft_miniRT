/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   vector_math_2.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/29 12:05:00 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/29 17:30:17 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

t_vector	hitpoint(t_vector v1, t_vector v2, double t)
{
	t_vector	new;

	new.x = v1.x + v2.x * t;
	new.y = v1.y + v2.y * t;
	new.z = v1.z + v2.z * t;
	return (new);
}

t_vector	add(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x + v2.x;
	new.y = v1.y + v2.y;
	new.z = v1.z + v2.z;
	return (new);
}

t_vector	subtract(t_vector v1, t_vector v2)
{
	t_vector	new;

	new.x = v1.x - v2.x;
	new.y = v1.y - v2.y;
	new.z = v1.z - v2.z;
	return (new);
}

t_vector	scale(t_vector v1, double scalar)
{
	t_vector	new;

	new.x = v1.x * scalar;
	new.y = v1.y * scalar;
	new.z = v1.z * scalar;
	return (new);
}

t_vector	copy_vector(t_vector copy)
{
	t_vector	new;

	new.x = copy.x;
	new.y = copy.y;
	new.z = copy.z;
	return (new);
}
