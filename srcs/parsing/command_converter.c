/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_converter.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:26:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/24 12:44:44 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_tokens_to_commands(t_token *token_list)
{
	t_command	*head;
	t_command	*new_cmd;
	int			arg_count;
	int			i;

	head = NULL;
	while (token_list)
	{
		arg_count = ft_count_args(token_list);
		new_cmd = ft_new_command(arg_count);
		if (!new_cmd)
			return (NULL);
		// Fill args and redirections by scanning until PIPE or end
		i = 0;
		while (token_list && token_list->type != PIPE)
		{
			if (token_list->type == WORD || token_list->type == VAR)
			{
				// assign argument pointer (assume ownership elsewhere)
				new_cmd->args[i++] = token_list->token;
			}
			else if (token_list->type == INPUT || token_list->type == TRUNC
				|| token_list->type == APPEND || token_list->type == HEREDOC)
			{
				if (token_list->next && (token_list->next->type == WORD
						|| token_list->next->type == VAR))
				{
					add_redir(new_cmd, token_list->type,
						token_list->next->token);
					// skip the file token
					token_list = token_list->next;
				}
				else
				{
					// syntax error or missing target: ignore gracefully
				}
			}
			token_list = token_list->next;
		}
		// ensure args are null-terminated
		new_cmd->args[i] = NULL;
		ft_add_back_command(&head, new_cmd);
		// if current token is a PIPE, advance past it
		if (token_list && token_list->type == PIPE)
			token_list = token_list->next;
	}
	return (head);
}
