/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:43:58 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/12 14:38:26 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

//return the current absolute path
char	*ft_pwd(void)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		ft_putendl_fd("error when allocating pwd", 2);
		return (NULL);
	}
	return (pwd);
}
