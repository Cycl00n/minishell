/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:55:22 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/03 13:25:39 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_env(char *cmd, char **env)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(cmd, ' ');
	while (env[i])
	{
		printf("%s\n", env[i]);
		i++;
	}
}
