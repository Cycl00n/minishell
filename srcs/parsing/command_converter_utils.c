/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_converter_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:26:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 22:00:00 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_new_command(void)
{
	t_command	*cmd;

	cmd = malloc(sizeof(t_command));
	if (!cmd)
		return (NULL);
	cmd->args = malloc(sizeof(char *) * 256);
	if (!cmd->args)
	{
		free(cmd);
		return (NULL);
	}
	cmd->next = NULL;
	return (cmd);
}

void	ft_add_back_command(t_command **head, t_command *new)
{
	t_command	*tmp;

	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

int	ft_count_args(t_token *token_list)
{
	int	count;

	count = 0;
	while (token_list && token_list->type != PIPE)
	{
		if (token_list->type == WORD || token_list->type == VAR)
			count++;
		token_list = token_list->next;
	}
	return (count);
}
