/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   mini_rt.h                                          :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 10:27:51 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 20:25:44 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_RT_H
# define MINI_RT_H

# include <stdio.h>
# include <errno.h>
# include <math.h>
# include <unistd.h>
# include <sys/stat.h>
# include <fcntl.h>

# include "mlx.h"
# include "libft.h"
# include "info.h"
# include "get_next_line.h"

/* Render */
t_mlx			*init_mlx(t_scene *scene);
t_img			*init_img(t_img *image, t_mlx *window);
t_mlx			*render(t_mlx *window, char **argv);

/* Miscellaneous functions */
int				error_and_exit(int error, char *prefix);
int				key_hook(int keycode, t_mlx *window);
int				close_rt(void);
void			my_mlx_pixel_put(t_img *image, int x, int y, int color);
void			reset_impact(t_impact *impact);
t_scene			*static_scene(void);

/* Parsing all the elements */
t_scene			*get_scene(char **argv, t_scene *scene);
int				read_and_parse(int fd, t_scene *scene);
int				parse_this_line(t_scene *scene, char **splitted);
int				parse_resolution(t_scene *scene, char **splitted);
int				parse_ambient(t_scene *scene, char **splitted);
int				parse_camera(t_scene *scene, char **splitted);
int				parse_light(t_scene *scene, char **splitted);
int				parse_sphere(t_scene *scene, char **splitted);
int				parse_plane(t_scene *scene, char **splitted);
int				parse_square(t_scene *scene, char **splitted);
int				parse_cylinder(t_scene *scene, char **splitted);
int				parse_triangle(t_scene *scene, char **splitted);

/* Error checking while parsing */
int				check_colors(char *colors);
int				check_orientation(char *ori);
int				check_fov(char *fov);
int				check_ratio(char *ratio);

/* Fill the struct with information */
int				fill_position(char *position, t_vector *pos_ptr);
int				fill_colors(char *colors, t_colors *color_ptr);
int				fill_orientation(char *orientation, t_vector *ori_ptr);

/* Camera */
t_matrix		camera_rotation(t_camera *camera);
t_vector		transform(t_vector pixel, t_matrix matrix);

/* Ray */
t_ray			*create_ray(t_ray *ray, t_vector hitpoint, t_vector light);
void			\
shoot_ray(t_img *img, t_ray *ray, t_impact *impact, t_scene *scene);
t_ray			\
*generate_ray(t_ray *ray, double w, double h, t_scene *scene);

/* Intersection */
void			make_image(t_img *img, t_scene *scene);
int				shade_object(t_impact *impact, t_scene *scene);
int				\
check_intersect(t_ray *ray, t_impact *impact, t_scene *scene);
void			\
intersect_sphere(t_ray *ray, t_impact *impact, t_sphere *sphere);
void			\
intersect_plane(t_ray *ray, t_impact *impact, t_plane *plane);
void			\
intersect_triangle(t_ray *ray, t_impact *impact, t_triangle *triangle);
void			\
intersect_square(t_ray *ray, t_impact *impact, t_square *square);
void			\
intersect_cylinder(t_ray *ray, t_impact *impact, t_cylinder *cylinder);

/* Color functions */
t_colors		color_add(t_colors color1, t_colors color2);
t_colors		color_scale(t_colors color1, float ratio);
t_colors		color_mult(t_colors color1, t_colors color2);
unsigned int	\
create_trgb(unsigned int t, unsigned int r, unsigned int g, unsigned int b);

/* Vector functions */
double			dot_product(t_vector v1, t_vector v2);
t_vector		cross_product(t_vector v1, t_vector v2);
double			magnitude(t_vector vector);
void			normalize(t_vector *vec);
t_vector		subtract(t_vector v1, t_vector v2);
t_vector		add(t_vector v1, t_vector v2);
t_vector		scale(t_vector v1, double scalar);
double			distance(t_vector p1, t_vector p2);
t_vector		new_vector(double x, double y, double z);
t_vector		hitpoint(t_vector v1, t_vector v2, double t);

/* BMP */
void			create_bmp(t_scene *scene, t_img *img);
void			header_bmp(t_scene *scene, int fd, t_img *img, int size);

/* Debug */
int				debugray(int keycode, int x, int y, t_scene *scene);
void			print_vect(t_vector vector, char *pre);
void			print_color(t_colors vector);

#endif