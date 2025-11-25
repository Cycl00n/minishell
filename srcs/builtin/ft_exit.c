/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 13:37:09 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/25 21:22:53 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_data *data)
{
	int	exit_code;

	exit_code = 0;
	if (data && data->cmd && data->cmd->args && data->cmd->args[1])
	{
		if (ft_strisnum(data->cmd->args[1]))
			exit_code = ft_atoi(data->cmd->args[1]);
		else
			exit_code = 1;
	}
	exit(exit_code);
}
