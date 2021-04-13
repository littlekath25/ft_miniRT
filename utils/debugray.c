/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   debugray.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: katherine <katherine@student.codam.nl>       +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/04/13 19:47:42 by katherine     #+#    #+#                 */
/*   Updated: 2021/04/13 20:52:31 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

void	ft_print_color(t_colors vector)
{
	printf("Color: %lf %lf %lf\n", vector.r, vector.g, vector.b);
}

void	ft_print_vect(t_vector vector, char *pre)
{
	printf("%s: %lf %lf %lf\n", pre, vector.x, vector.y, vector.z);
}

int    debugray(int keycode, int x, int y, t_scene *scene)
{
	t_ray 		*ray;
	t_impact 	*impact;
	int			color;
	
	scene->debug = 1;
	impact = (t_impact *)ft_calloc(sizeof(t_impact), 1);
	ray = (t_ray *)ft_calloc(sizeof(t_ray), 1);
	ray = ft_generate_ray(ray, x, y, scene);
	ft_check_intersect(ray, impact, scene);
	ft_print_color(impact->rgb);
	color = ft_shade_object(ray, impact, scene);

	printf("T: %lf\n", impact->near);
	ft_print_vect(impact->hitpoint, "Hitpoint");
	ft_print_vect(impact->normal, "Normal");
	ft_print_color(impact->rgb);

	printf("\n\n");
	free(impact);
	free(ray);
	scene->debug = 0;
	return (0);
}
