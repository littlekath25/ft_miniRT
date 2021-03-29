/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_lstadd_back.c                                   :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/11/13 18:55:59 by kfu           #+#    #+#                 */
/*   Updated: 2021/03/17 12:50:41 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*node;

	node = *lst;
	if (node != NULL)
	{
		while (node->next != NULL)
			node = node->next;
		node->next = new;
	}
	else
		*lst = new;
}
