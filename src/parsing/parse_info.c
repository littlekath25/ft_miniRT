/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   parse_info.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/27 17:21:55 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/03 11:29:57 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_parse_resolution(t_scene *scene, char **splitted)
{
	static int	resolution;
	int			width;
	int			height;

	if (resolution == 1)
		ft_error_and_exit(1, "Resolution - ");
	resolution = 0;
	width = ft_atoi(splitted[1]);
	height = ft_atoi(splitted[2]);
	if (width < 0 || height < 0)
		ft_error_and_exit(2, "Resolution - ");
	scene->width = width;
	scene->height = height;
	resolution = 1;
	return (1);
}

int	ft_parse_ambient(t_scene *scene, char **splitted)
{
	static int	ambient;
	char		*category;

	category = "Ambient - ";
	if (ambient == 1)
		ft_error_and_exit(1, category);
	ambient = 0;
	if (!(ft_check_ratio(splitted[1])) || !(ft_check_colors(splitted[2])))
		ft_error_and_exit(2, category);
	scene->ambient.ratio = ft_atof(splitted[1]);
	ft_fill_colors(splitted[2], &scene->ambient.colors);
	scene->ambient.colors = ft_color_amb(scene->ambient.colors, scene->ambient.ratio);
	ambient = 1;
	return (1);
}

int	ft_parse_camera(t_scene *scene, char **splitted)
{
	t_list		*new_node;
	t_camera	*camera;
	char		*category;

	category = "Camera - ";
	if (!(ft_check_fov(splitted[3])) || !(ft_check_orientation(splitted[2])))
		ft_error_and_exit(2, category);
	camera = (t_camera *)ft_calloc(sizeof(t_camera), 1);
	new_node = ft_lstnew(camera);
	if (!camera || !new_node)
		ft_error_and_exit(3, category);
	ft_lstadd_back(&scene->camera, new_node);
	ft_fill_position(splitted[1], &camera->pos);
	ft_fill_orientation(splitted[2], &camera->ori);
	camera->fov = ft_atoi(splitted[3]);
	return (1);
}

int	ft_parse_light(t_scene *scene, char **splitted)
{
	t_list	*new_node;
	t_light	*light;
	char	*category;

	category = "Light - ";
	if (!(ft_check_ratio(splitted[2])) || !(ft_check_colors(splitted[3])))
		ft_error_and_exit(2, category);
	light = (t_light *)ft_calloc(sizeof(t_light), 1);
	new_node = ft_lstnew(light);
	if (!light || !new_node)
		ft_error_and_exit(3, category);
	ft_lstadd_back(&scene->light, new_node);
	if ((ft_fill_position(splitted[1], &light->pos)) == -1 || \
	(ft_fill_colors(splitted[3], &light->colors)) == -1)
		return (-1);
	light->ratio = ft_atof(splitted[2]);
	return (1);
}
