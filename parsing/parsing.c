/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 08:32:00 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/03 14:41:05 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parsing(t_data *data)
{
	int	i;

	i = 0;
	data->cmd->args = ft_split(data->input, ' ');
	while (data->cmd->args[i])
	{
		printf("[%d] %s\n", i, data->cmd->args[i]);
		i++;
	}
}
