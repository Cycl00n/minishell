/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_parser.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:05:15 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 20:27:49 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(int t)
{
	return (t == INPUT || t == TRUNC || t == APPEND || t == HEREDOC);
}

static t_token	*process_token(t_token *tok, t_command *curr)
{
	if (tok->type == WORD)
		add_arg(curr, tok->token);
	else if (is_redirection(tok->type))
	{
		if (!tok->next || tok->next->type != WORD)
		{
			printf("minishell: syntax error near unexpected token");
			return (NULL);
		}
		add_redir(curr, tok->type, tok->next->token);
		tok = tok->next;
	}
	else if (tok->type == PIPE)
		curr->next = new_cmd();
	return (tok->next);
}

t_command	*parse_tokens(t_token *tok)
{
	t_command	*head;
	t_command	*curr;

	head = new_cmd();
	curr = head;
	while (tok)
	{
		tok = process_token(tok, curr);
		if (tok && tok->type == PIPE)
			curr = curr->next;
	}
	return (head);
}
