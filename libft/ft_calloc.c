/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_calloc.c                                        :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2020/10/29 16:41:12 by kfu           #+#    #+#                 */
/*   Updated: 2021/04/29 19:41:03 by katherine     ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

void	*ft_calloc(size_t size, size_t count)
{
	char	*ptr;
	size_t	i;

	i = 0;
	if (size < i || count < i)
		return (NULL);
	ptr = malloc(size * count);
	if (ptr == NULL)
		return ((void *) 0);
	while (i < (size * count))
	{
		ptr[i] = '\0';
		i++;
	}
	return ((void *)ptr);
}
