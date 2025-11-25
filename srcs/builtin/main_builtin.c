/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_builtin.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 20:45:09 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/25 21:22:29 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_commands(t_data *data)
{
	char	*cmd;

	if (!data || !data->cmd || !data->cmd->args)
		return ;
	cmd = data->cmd->args[0];
	if (!ft_strcmp(cmd, "echo"))
		builtin_echo(data);
	/*else if (!ft_strcmp(cmd, "cd"))
		builtin_cd(data);
	else if (!ft_strcmp(cmd, "pwd"))
		builtin_pwd(data);
	else if (!ft_strcmp(cmd, "export"))
		builtin_export(data);
	else if (!ft_strcmp(cmd, "unset"))
		builtin_unset(data);
	else if (!ft_strcmp(cmd, "env"))
		builtin_env(data);*/
	else if (!ft_strcmp(cmd, "exit"))
		builtin_exit(data);
}
