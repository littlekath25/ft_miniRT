/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   error.c                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/19 14:22:28 by kfu           #+#    #+#                 */
/*   Updated: 2021/05/02 09:37:54 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	check_orientation(char *orientation)
{
	t_vector	vec;
	int			ret;
	int			words;
	char		**ori;

	ret = 1;
	ori = ft_split(orientation, ',', &words);
	if (ori == NULL)
		return (-1);
	if (words != 3)
		error_and_exit(0, "Invalid orientation values");
	vec.x = ft_atof(ori[0]);
	vec.y = ft_atof(ori[1]);
	vec.z = ft_atof(ori[2]);
	if (vec.x < -1 || vec.y < -1 || vec.z < -1 \
	|| vec.x > 1 || vec.y > 1 || vec.z > 1)
		ret = 0;
	if (vec.x + vec.y + vec.z > 1)
		normalize(&vec);
	ft_free_split(ori);
	return (ret);
}

int	check_fov(char *fov)
{
	float	f;

	f = ft_atof(fov);
	if (f < 0 || f >= 180)
		return (0);
	return (1);
}

int	check_ratio(char *ratio)
{
	float	rat;

	rat = ft_atof(ratio);
	if (rat < 0 || rat > 1)
		return (0);
	return (1);
}

int	check_colors(char *colors)
{
	t_colors	color;
	int			ret;
	int			words;
	char		**col;

	ret = 1;
	col = ft_split(colors, ',', &words);
	if (col == NULL)
		return (-1);
	if (words != 3)
		error_and_exit(0, "Invalid colors values");
	color.r = ft_atoi(col[0]);
	color.g = ft_atoi(col[1]);
	color.b = ft_atoi(col[2]);
	if (color.r < 0 || color.g < 0 || color.b < 0 \
	|| color.r > 255 || color.g  > 255 || color.b > 255)
		ret = 0;
	ft_free_split(col);
	return (ret);
}

int	error_and_exit(int error, char *prefix)
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
