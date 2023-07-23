/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakashi <rtakashi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 22:14:08 by reira             #+#    #+#             */
/*   Updated: 2023/06/12 20:46:29 by rtakashi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "pipex.h"

char	*ft_free(char **str)
{
	size_t	i;

	if (str == NULL)
		return (NULL);
	i = 0;
	while (str[i] != NULL)
	{
		free(str[i]);
		i++;
	}
	free(str);
	return (NULL);
}

void	free_perror_exit(char *str, char **free1, char **free2)
{
	if (free1 != NULL)
		ft_free(free1);
	if (free2 != NULL)
		ft_free(free2);
	perror(str);
	exit(EXIT_FAILURE);
}

void	free_put_error_exit(char **str, char **free)
{
	size_t	i;

	if (free != NULL)
		ft_free(free);
	i = 0;
	ft_putstr_fd(str[0], 2);
	ft_putstr_fd(": command not found\n", 2);
	if (str != NULL)
		ft_free(str);
	exit(EXIT_FAILURE);
}
