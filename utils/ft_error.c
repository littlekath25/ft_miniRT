/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_error.c                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 14:22:28 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/15 15:57:37 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_check_orientation(char *orientation)
{
	float	x;
	float	y;
	float	z;
	int		ret;
	char	**ori;

	ret = 1;
	ori = ft_split(orientation, ',');
	if (ori == NULL)
		return (-1);
	x = ft_atof(ori[0]);
	y = ft_atof(ori[1]);
	z = ft_atof(ori[2]);
	if (x < -1 || y < -1 || z < -1 || x > 1 || y > 1 || z > 1)
		ret = 0;
	ft_free_split(ori);
	return (ret);
}

int	ft_check_fov(char *fov)
{
	float	f;

	f = ft_atof(fov);
	if (f < 0 || f > 180)
		return (0);
	return (1);
}

int	ft_check_ratio(char *ratio)
{
	float	rat;

	rat = ft_atof(ratio);
	if (rat < 0 || rat > 1)
		return (0);
	return (1);
}

int	ft_check_colors(char *colors)
{
	int		r;
	int		g;
	int		b;
	int		ret;
	char	**col;

	ret = 1;
	col = ft_split(colors, ',');
	if (col == NULL)
		return (-1);
	r = ft_atoi(col[0]);
	g = ft_atoi(col[1]);
	b = ft_atoi(col[2]);
	if (r < 0 || g < 0 || b < 0 || r > 255 || g > 255 || b > 255)
		ret = 0;
	ft_free_split(col);
	return (ret);
}

int	ft_error_and_exit(int error, char *prefix)
{
	if (error == 0)
		printf("Error\n%s\n", prefix);
	if (error == 1)
		printf("Error\n%sMultiple definitions\n", prefix);
	if (error == 2)
		printf("Error\n%sInvalid value\n", prefix);
	if (error == 3)
		printf("Error\n%sMalloc fail\n", prefix);
	exit(-1);
}
