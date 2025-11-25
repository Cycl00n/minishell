/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 16:00:45 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/12 14:38:46 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_unset(char **args, t_env **env)
{
	char	*name;
	int		index;

	if (!env || !args || !args[0])
		return ;
	index = 0;
	while (args[index])
	{
		if (args[index] && args[index][0])
		{
			name = args[index];
			ft_rm_env(name, env);
		}
		index++;
	}
}
