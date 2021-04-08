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

// static t_vector	calculate_rot(t_vector *c2, t_vector *c3, t_vector rot, t_vector to)
// {
// 	t_vector	c1;
// 	t_vector	v;
// 	float	c;
// 	float	s;
// 	float	r;

// 	v = ft_cross_product(to, rot);
// 	c = ft_dot_product(rot, to);
// 	s = pow(ft_magnitude(v), 2);
// 	r = ((1 - c) / s);
// 	c1 = ft_new_vector(-r * (pow(v.y, 2) + pow(v.z, 2)) + 1, r * v.x * \
// 				v.y - v.z, r * v.x * v.z + v.y);
// 	(*c2) = ft_new_vector(r * v.x * v.y + v.z, -r * (pow(v.x, 2) + \
// 					pow(v.z, 2)) + 1, r * v.y * v.x - v.x);
// 	(*c3) = ft_new_vector(r * v.x * v.z - v.y, r * v.y * v.z - v.x, -r * \
// 					(pow(v.x, 2) + pow(v.y, 2)) + 1);
// 	return (c1);
// }

// static t_vector	apply_rot(t_vector pos, t_vector dir, t_vector rot)
// {
// 	t_vector	c1;
// 	t_vector	c2;
// 	t_vector	c3;
// 	t_vector	prev;

// 	if (dir.x == 0 && dir.y < 0 && dir.z == 0)
// 		pos = ft_new_vector(pos.x, pos.y, -pos.z);
// 	if (!(dir.x == 0 && dir.y != 0 && dir.z == 0))
// 	{
// 		prev = pos;
// 		c1 = calculate_rot(&c2, &c3, rot, dir);
// 		pos = ft_new_vector(ft_dot_product(c1, prev), ft_dot_product(c2, prev), ft_dot_product(c3, prev));
// 	}
// 	return (pos);
// }

// static float		inter_plane(t_ray *ray, t_square *square)
// {
// 	float		a;
// 	float		b;
// 	float		t;
// 	t_vector	tmp;

// 	tmp = ft_subtract(ray->pos, square->pos);
// 	a = ft_dot_product(tmp, square->normal);
// 	b = ft_dot_product(ray->dir, square->normal);
// 	if (b == 0 || (a < 0 && b < 0) || (a > 0 && b > 0))
// 		return (0);
// 	t = -a / b;
// 	if (t < 0)
// 		return (0);
// 	return (t);
// }

// static double		ft_solve(t_square *square, t_ray *ray, t_impact *impact)
// {
// 	float		t_near;
// 	float		a;
// 	t_vector	p;
// 	t_vector	data;

// 	if (!(t_near = inter_plane(ray, square)))
// 		return (INFINITY);
// 	data = ft_scale(ray->dir, t_near);
// 	p = ft_add(ray->pos, data);
// 	if (square->normal.x != 0 || square->normal.y == 0 || square->normal.z != 0)
// 		p = apply_rot(p, square->normal, ft_new_vector(0, 1, 0));
// 	a = square->pos.x - square->side / 2;
// 	data.x = square->pos.x + square->side / 2;
// 	data.y = square->pos.z - square->side / 2;
// 	data.z = square->pos.z + square->side / 2;
// 	if (!((p.x >= a && p.x <= data.x) && (p.z <= data.z && p.z >= data.y)))
// 		return (INFINITY);
// 	return (t_near);
// }

static double       orient(t_vector a, t_vector b, t_vector c, t_vector n)
{
    t_vector ba;
    t_vector ca;
    t_vector cross;
    double dot;

    ba = ft_subtract(b, a);
    ca = ft_subtract(c, a);
    cross = ft_cross_product(ba, ca);
    dot = ft_dot_product(cross, n);
    return (dot);
}

static double		ft_solve(t_ray *ray, t_impact *impact, t_square *square)
{
    t_vector p[4];
    t_plane *plane;
    t_impact *impact_plane;
    t_vector hitpoint;
    double  o[4];

    plane = (t_plane *)ft_calloc(sizeof(t_plane), 1);
    impact_plane = (t_impact *)ft_calloc(sizeof(t_impact), 1);
    plane->pos = square->pos;
    plane->normal = square->normal;
    ft_intersect_plane(ray, impact_plane, plane);
    p[0] = ft_new_vector(square->pos.x - square->side / 2, square->pos.y + square->side / 2, square->pos.z);
    p[1] = ft_new_vector(square->pos.x + square->side / 2, square->pos.y + square->side / 2, square->pos.z);
    p[2] = ft_new_vector(square->pos.x + square->side / 2, square->pos.y - square->side / 2, square->pos.z);
    p[3] = ft_new_vector(square->pos.x - square->side / 2, square->pos.y - square->side / 2, square->pos.z);

    o[0] = orient(impact->hitpoint, p[0], p[1], square->normal);
    o[1] = orient(impact->hitpoint, p[1], p[2], square->normal);
    o[2] = orient(impact->hitpoint, p[2], p[3], square->normal);
    o[3] = orient(impact->hitpoint, p[3], p[0], square->normal);
    
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