/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   info.h                                             :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 12:23:55 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 21:43:49 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef INFO_H
# define INFO_H

# ifndef LINUX
#  define LINUX 0
# endif

# define RAY_MIN 0.00001
# define BMP_HEADER 54

typedef enum e_obj
{
	SP,
	PL,
	SQ,
	CY,
	TR
}	t_obj;

typedef struct s_quad
{
	double	a;
	double	b;
	double	c;
	double	disc;
}	t_quad;

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
	double			fov;
	double			length;
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

typedef struct s_solve_cylinder
{
	t_quad		quad;
	double		t_near;
	double		t_1;
	double		t_2;
}	t_solve_cylinder;

typedef struct s_triangle
{
	t_obj				identifier;
	t_vector			pos1;
	t_vector			pos2;
	t_vector			pos3;
	t_colors			colors;
}	t_triangle;

typedef struct s_solve_triangle
{
	t_vector	e1;
	t_vector	e2;
	t_vector	p;
	t_vector	t;
	t_vector	q;
	double		d;
	double		t_near;
	double		u;
	double		v;
}	t_solve_triangle;

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
	t_colors	rgb;
	t_vector	hitpoint;
	t_vector	normal;
}	t_impact;

typedef struct s_img
{
	void	*img;
	void	*address;
	int		bpp;
	int		line_len;
	int		endian;
	char	*data;
}	t_img;

typedef struct s_mlx
{
	void	*ptr;
	void	*win;
	t_img	*image;
}	t_mlx;

typedef struct s_scene
{
	int			debug;
	int			bmp;
	int			width;
	int			height;
	t_mlx		mlx;
	t_ambient	ambient;
	t_list		*current_cam;
	t_list		*camera;
	t_list		*light;
	t_list		*objects;
}	t_scene;

typedef union u_matrix
{
	double		map[4][4];
	struct
	{
		t_vector	right;
		double		x;
		t_vector	up;
		double		y;
		t_vector	forward;
		double		z;
		t_vector	origin;
		double		w;
	};
}	t_matrix;

#endif
