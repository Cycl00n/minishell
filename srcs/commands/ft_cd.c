/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:49:48 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/10 15:09:44 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//change the current path to the one specified
int	ft_cd(char *path)
{
	if (!path || !path[0])
		return (-1);
	return (chdir(path));
}