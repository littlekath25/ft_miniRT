/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   fill_struct.c                                      :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/03/06 14:16:38 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/16 21:16:14 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "mini_rt.h"

int	ft_fill_position(char *position, t_vector *pos_ptr)
{
	char		**pos;

	pos = ft_split(position, ',');
	if (pos == NULL)
		return (-1);
	pos_ptr->x = ft_atof(pos[0]);
	pos_ptr->y = ft_atof(pos[1]);
	pos_ptr->z = ft_atof(pos[2]);
	ft_free_split(pos);
	return (1);
}

int	ft_fill_colors(char *colors, t_colors *color_ptr)
{
	char		**col;

	col = ft_split(colors, ',');
	if (col == NULL)
		return (-1);
	color_ptr->r = ft_atoi(col[0]);
	color_ptr->g = ft_atoi(col[1]);
	color_ptr->b = ft_atoi(col[2]);
	ft_free_split(col);
	return (1);
}

int	ft_fill_orientation(char *orientation, t_vector *ori_ptr)
{
	char		**ori;

	ori = ft_split(orientation, ',');
	if (ori == NULL)
		return (-1);
	ori_ptr->x = ft_atof(ori[0]);
	ori_ptr->y = ft_atof(ori[1]);
	ori_ptr->z = ft_atof(ori[2]);
	ft_free_split(ori);
	return (1);
}
