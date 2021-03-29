/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_object.c                                     :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 13:41:17 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/17 12:50:04 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_sphere(t_scene *scene, char **splitted)
{
	t_list		*new_node;
	t_sphere	*sphere;
	char		*category;

	category = "Sphere - ";
	if (!(ft_check_colors(splitted[3])))
		ft_error_and_exit(2, category);
	sphere = (t_sphere *)ft_calloc(sizeof(t_sphere), 1);
	new_node = ft_lstnew(sphere);
	if (!sphere || !new_node)
		ft_error_and_exit(3, category);
	sphere->identifier = SP;
	ft_lstadd_back(&scene->objects, new_node);
	ft_fill_position(splitted[1], &sphere->pos);
	ft_fill_colors(splitted[3], &sphere->colors);
	sphere->diameter = ft_atof(splitted[2]);
	return (1);
}

int	ft_parse_plane(t_scene *scene, char **splitted)
{
	t_list	*new_node;
	t_plane	*plane;
	char	*category;

	category = "Plane - ";
	if (!(ft_check_orientation(splitted[2])) || !(ft_check_colors(splitted[3])))
		ft_error_and_exit(2, category);
	plane = (t_plane *)ft_calloc(sizeof(t_plane), 1);
	new_node = ft_lstnew(plane);
	if (!plane || !new_node)
		ft_error_and_exit(3, category);
	plane->identifier = PL;
	ft_lstadd_back(&scene->objects, new_node);
	ft_fill_position(splitted[1], &plane->pos);
	ft_fill_colors(splitted[3], &plane->colors);
	ft_fill_orientation(splitted[2], &plane->ori);
	return (1);
}

int	ft_parse_square(t_scene *scene, char **splitted)
{
	t_list		*new_node;
	t_square	*square;
	char		*category;

	category = "Square - ";
	if (!(ft_check_orientation(splitted[2])) || !(ft_check_colors(splitted[4])))
		ft_error_and_exit(2, category);
	square = (t_square *)ft_calloc(sizeof(t_square), 1);
	new_node = ft_lstnew(square);
	if (!square || !new_node)
		ft_error_and_exit(3, category);
	square->identifier = SQ;
	ft_lstadd_back(&scene->objects, new_node);
	ft_fill_position(splitted[1], &square->pos);
	ft_fill_colors(splitted[4], &square->colors);
	ft_fill_orientation(splitted[2], &square->ori);
	square->side = ft_atof(splitted[3]);
	return (1);
}

int	ft_parse_cylinder(t_scene *scene, char **splitted)
{
	t_list		*new_node;
	t_cylinder	*cylinder;
	char		*category;

	category = "Cylinder - ";
	if (!(ft_check_orientation(splitted[2])) || !(ft_check_colors(splitted[5])))
		ft_error_and_exit(2, category);
	cylinder = (t_cylinder *)ft_calloc(sizeof(t_cylinder), 1);
	new_node = ft_lstnew(cylinder);
	if (!cylinder || !new_node)
		ft_error_and_exit(3, category);
	cylinder->identifier = CY;
	ft_lstadd_back(&scene->objects, new_node);
	ft_fill_position(splitted[1], &cylinder->pos);
	ft_fill_colors(splitted[5], &cylinder->colors);
	ft_fill_orientation(splitted[2], &cylinder->ori);
	cylinder->diameter = ft_atof(splitted[3]);
	cylinder->height = ft_atof(splitted[4]);
	return (1);
}

int	ft_parse_triangle(t_scene *scene, char **splitted)
{
	t_list		*new_node;
	t_triangle	*triangle;
	char		*category;

	category = "Triangle - ";
	if (!(ft_check_colors(splitted[4])))
		ft_error_and_exit(2, category);
	triangle = (t_triangle *)ft_calloc(sizeof(t_triangle), 1);
	new_node = ft_lstnew(triangle);
	if (!triangle || !new_node)
		ft_error_and_exit(3, category);
	triangle->identifier = TR;
	ft_lstadd_back(&scene->objects, new_node);
	ft_fill_position(splitted[1], &triangle->pos1);
	ft_fill_position(splitted[2], &triangle->pos2);
	ft_fill_position(splitted[3], &triangle->pos3);
	ft_fill_colors(splitted[4], &triangle->colors);
	return (1);
}
