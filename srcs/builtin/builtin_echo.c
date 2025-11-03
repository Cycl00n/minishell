/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 11:06:20 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/03 11:38:09 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char *readl)
{
	char	**args;
	int		i;

	i = 1;
	if (!readl || *readl == '\0')
		return ;
	args = ft_split(readl, ' ');
	if (!ft_strncmp(args[1], "-n", 2))
		i = 2;
	while (args[i])
	{
		ft_putstr_fd(args[i], STDOUT_FILENO);
		if (args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	if (ft_strncmp(args[1], "-n", 2))
		ft_putstr_fd("\n", STDOUT_FILENO);
}
