/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_to_cmd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:26:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 18:58:37 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_command	*ft_tokens_to_commands(t_token *token_list)
{
	t_command	*head;
	t_command	*new_cmd;
	int			arg_count;

	head = NULL;
	while (token_list)
	{
		arg_count = ft_count_args(token_list);
		new_cmd = ft_new_command();
		if (!new_cmd)
			return (NULL);
		new_cmd->args = ft_build_args(token_list, arg_count);
		ft_add_back_command(&head, new_cmd);
		token_list = ft_skip_to_next_pipe(token_list);
	}
	return (head);
}
