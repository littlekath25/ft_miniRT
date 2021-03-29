/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_rt.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:27:51 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/29 16:43:35 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdio.h>
# include <errno.h>
// # include <X11/X.h>
# include <math.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"
# include "info.h"
# include "get_next_line.h"

/* Miscellaneous functions */
int			ft_error_and_exit(int error, char *prefix);
int			ft_create_trgb(int t, int r, int g, int b);
int			key_hook(int keycode, t_mlx *window);
t_mlx		*ft_init_mlx(t_scene *scene);
t_img		*ft_init_img(t_img *image, t_mlx *window, t_scene *scene);
void		my_mlx_pixel_put(t_img *image, int x, int y, int color);
t_vector	ft_new_vector(double x, double y, double z);
t_vector	ft_add_vector(t_vector v1, t_vector v2);
t_vector	ft_copy_vector(t_vector copy);
t_vector	ft_hitpoint(t_vector v1, t_vector v2, double t);

/* Vector functions */
double		ft_dot_product(t_vector v1, t_vector v2);
t_vector	ft_cross_product(t_vector v1, t_vector v2);
double		ft_magnitude(t_vector vector);
void		ft_normalize(t_vector *vec);
t_vector	ft_subtract(t_vector v1, t_vector v2);
t_vector	ft_add(t_vector v1, t_vector v2);
t_vector	ft_scale(t_vector v1, double scalar);

/* Error checking while parsing */
int			ft_check_colors(char *colors);
int			ft_check_orientation(char *ori);
int			ft_check_fov(char *fov);
int			ft_check_ratio(char *ratio);

/* Parsing all the elements */
t_scene		*ft_get_scene(int argc, char **argv, t_scene *scene);
int			ft_read_and_parse(int fd, t_scene *scene);
int			ft_parse_this_line(t_scene *scene, char **splitted);
int			ft_parse_resolution(t_scene *scene, char **splitted);
int			ft_parse_ambient(t_scene *scene, char **splitted);
int			ft_parse_camera(t_scene *scene, char **splitted);
int			ft_parse_light(t_scene *scene, char **splitted);
int			ft_parse_sphere(t_scene *scene, char **splitted);
int			ft_parse_plane(t_scene *scene, char **splitted);
int			ft_parse_square(t_scene *scene, char **splitted);
int			ft_parse_cylinder(t_scene *scene, char **splitted);
int			ft_parse_triangle(t_scene *scene, char **splitted);

/* Fill the struct with information */
int			ft_fill_position(char *position, t_vector *pos_ptr);
int			ft_fill_colors(char *colors, t_colors *color_ptr);
int			ft_fill_orientation(char *orientation, t_vector *ori_ptr);

/* Intersection */
void		ft_make_image(t_img *img, t_scene *scene);
t_ray		*ft_generate_ray(t_ray *ray, int w, int h, t_scene *scene);
t_impact	*ft_check_intersect(t_ray *ray, t_impact *impact, t_camera *camera, t_scene *scene);
void		ft_intersect_sphere(t_ray *ray, t_impact *impact, t_camera *camera, t_sphere *object);
int			ft_shade_object(t_ray *ray, t_impact *impact, t_scene *scene);

#endif