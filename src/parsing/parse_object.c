/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 13:41:17 by kfu           #+#    #+#                 */
/*   Updated: 2021/05/01 23:18:40 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	parse_sphere(t_scene *scene, char **splitted, int words)
{
	t_list		*new_node;
	t_sphere	*sphere;
	char		*category;

	if (words != 4)
		error_and_exit(0, "Wrong sphere values");
	category = "Sphere - ";
	sphere = (t_sphere *)ft_calloc(sizeof(t_sphere), 1);
	new_node = ft_lstnew(sphere);
	if (!sphere || !new_node)
		error_and_exit(3, category);
	sphere->identifier = SP;
	ft_lstadd_back(&scene->objects, new_node);
	fill_position(splitted[1], &sphere->pos);
	fill_colors(splitted[3], &sphere->colors);
	sphere->diameter = ft_atof(splitted[2]) / 2;
	return (1);
}

int	parse_plane(t_scene *scene, char **splitted, int words)
{
	t_list	*new_node;
	t_plane	*plane;
	char	*category;

	if (words != 4)
		error_and_exit(0, "Wrong plane values");
	category = "Plane - ";
	plane = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	new_node = ft_lstnew(plane);
	if (!plane || !new_node)
		error_and_exit(3, category);
	plane->identifier = PL;
	ft_lstadd_back(&scene->objects, new_node);
	fill_position(splitted[1], &plane->pos);
	fill_colors(splitted[3], &plane->colors);
	fill_orientation(splitted[2], &plane->ori);
	return (1);
}

int	parse_square(t_scene *scene, char **splitted, int words)
{
	t_list		*new_node;
	t_square	*square;
	char		*category;

	if (words != 5)
		error_and_exit(0, "Wrong square values");
	category = "Square - ";
	square = (t_square *)ft_calloc(sizeof(t_square), 1);
	new_node = ft_lstnew(square);
	if (!square || !new_node)
		error_and_exit(3, category);
	square->identifier = SQ;
	ft_lstadd_back(&scene->objects, new_node);
	fill_position(splitted[1], &square->pos);
	fill_colors(splitted[4], &square->colors);
	fill_orientation(splitted[2], &square->ori);
	square->side = ft_atof(splitted[3]);
	return (1);
}

int	parse_cylinder(t_scene *scene, char **splitted, int words)
{
	t_list		*new_node;
	t_cylinder	*cylinder;
	char		*category;

	if (words != 6)
		error_and_exit(0, "Wrong cylinder values");
	category = "Cylinder - ";
	cylinder = (t_cylinder *)ft_calloc(sizeof(t_cylinder), 1);
	new_node = ft_lstnew(cylinder);
	if (!cylinder || !new_node)
		error_and_exit(3, category);
	cylinder->identifier = CY;
	ft_lstadd_back(&scene->objects, new_node);
	fill_position(splitted[1], &cylinder->pos);
	fill_colors(splitted[5], &cylinder->colors);
	fill_orientation(splitted[2], &cylinder->ori);
	cylinder->diameter = ft_atof(splitted[3]) / 2;
	cylinder->height = ft_atof(splitted[4]);
	return (1);
}

int	parse_triangle(t_scene *scene, char **splitted, int words)
{
	t_list		*new_node;
	t_triangle	*triangle;
	char		*category;

	if (words != 5)
		error_and_exit(0, "Wrong triangle values");
	category = "Triangle - ";
	triangle = (t_triangle *)ft_calloc(sizeof(t_triangle), 1);
	new_node = ft_lstnew(triangle);
	if (!triangle || !new_node)
		error_and_exit(3, category);
	triangle->identifier = TR;
	ft_lstadd_back(&scene->objects, new_node);
	fill_position(splitted[1], &triangle->pos1);
	fill_position(splitted[2], &triangle->pos2);
	fill_position(splitted[3], &triangle->pos3);
	fill_colors(splitted[4], &triangle->colors);
	return (1);
}
