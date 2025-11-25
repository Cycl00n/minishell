/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:33:02 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/25 15:12:49 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_commands(t_data *data)
{
	if (!data || !data->cmd || !data->cmd->args || !data->cmd->args[0])
		return (0);
	if (!ft_strcmp(data->cmd->args[0], "echo"))
	{
		builtin_echo(data);
		return (1);
	}
	else
		return (0);
}

void	builtin_echo(t_data *data)
{
	int	i;

	i = 1;
	if (!data->cmd->args || !data->cmd->args[1])
		return ;
	if (ft_strcmp(data->cmd->args[1], "-n"))
	{
		//
	}
	while (data->cmd->args[i])
	{
		ft_putstr_fd(data->cmd->args[i], STDOUT_FILENO);
		if (data->cmd->args[i + 1])
			ft_putstr_fd(" ", STDOUT_FILENO);
		i++;
	}
	ft_putstr_fd("\n", STDOUT_FILENO);
}
