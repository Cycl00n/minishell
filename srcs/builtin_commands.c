/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_commands.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 11:53:54 by clnicola          #+#    #+#             */
/*   Updated: 2025/10/23 13:02:58 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(char *cmd)
{
	printf("%s\n", &cmd[4]);
	return ;
}

void	builtin_exit(char *readl, char *prompt)
{
	char	**args;

	args = ft_split(readl, ' ');
	printf("exit\n");
	free(readl);
	free(prompt);
	if (args[1] && args[2])
	{
		printf("minishell: exit: too many arguments\n");
		free(args);
		exit(1);
	}
	else if (args[1] && (!ft_strisnum(args[1])))
	{
		printf("minishell: exit: %s : numeric argument required\n", args[1]);
		free(args);
		exit(255);
	}
	else if (args[1])
	{
		exit(ft_atoi(args[1]));
		free(args);
	}
	else
		exit(0);
}
