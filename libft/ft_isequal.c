/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   ft_isequal.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: kfu <kfu@student.codam.nl>                   +#+                     */
/*                                                   +#+                      */
/*   Created: 2021/02/25 14:47:26 by kfu           #+#    #+#                 */
/*   Updated: 2021/02/26 15:16:44 by kfu           ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

int	ft_isequal(const char *str1, const char *str2)
{
	int	i;

	i = 0;
	while (str1[i] == str2[i])
	{
		if (str1[i] == '\0' || str2[i] == '\0')
			break ;
		i++;
	}
	if (str1[i] == '\0' && str2[i] == '\0')
		return (1);
	return (0);
}
