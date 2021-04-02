/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 12:23:55 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/02 16:03:22 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# define RAY_MIN 0.00001

# ifdef LINUX
#  define ESC		65307
# else
#  define ESC		53
# endif

typedef enum e_obj
{
	SP,
	PL,
	SQ,
	CY,
	TR
}	t_obj;

typedef struct s_colors
{
	float	r;
	float	g;
	float	b;
}	t_colors;

typedef struct s_vector
{
	double	x;
	double	y;
	double	z;
}	t_vector;

typedef struct s_ambient
{
	double		ratio;
	t_colors	colors;
}	t_ambient;

typedef struct s_camera
{
	t_vector		pos;
	t_vector		ori;
	int				fov;
}	t_camera;

typedef struct s_light
{
	t_vector		pos;
	t_colors		colors;
	double			ratio;
}	t_light;

typedef struct s_sphere
{
	t_obj			identifier;
	t_vector		pos;
	t_colors		colors;
	double			diameter;
}	t_sphere;

typedef struct s_plane
{
	t_obj			identifier;
	t_vector		pos;
	t_colors		colors;
	t_vector		ori;
}	t_plane;

typedef struct s_square
{
	t_obj			identifier;
	t_vector		pos;
	t_colors		colors;
	t_vector		ori;
	double			side;
}	t_square;

typedef struct s_cylinder
{
	t_obj				identifier;
	t_vector			pos;
	t_colors			colors;
	t_vector			ori;
	double				diameter;
	double				height;
}	t_cylinder;

typedef struct s_triangle
{
	t_obj				identifier;
	t_vector			pos1;
	t_vector			pos2;
	t_vector			pos3;
	t_colors			colors;
}	t_triangle;

typedef struct s_ray
{
	t_vector	pos;
	t_vector	dir;
	double		len;
}	t_ray;

typedef struct s_impact
{
	int			intersect;
	double		near;
	float		angle;
	int			color;
	t_colors	rgb;
	t_vector	hitpoint;
	t_vector	object_pos;
}	t_impact;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
}	t_mlx;

typedef struct s_img
{
	void	*img;
	void	*address;
	int		bpp;
	int		line_len;
	int		endian;
}	t_img;

typedef struct s_scene
{
	int			width;
	int			height;
	t_mlx		mlx;
	t_ambient	ambient;
	t_list		*camera;
	t_list		*light;
	t_list		*objects;
}	t_scene;

#endif
