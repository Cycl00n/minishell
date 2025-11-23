/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 17:05:15 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 20:26:23 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_redirection(int t)
{
	if (t == INPUT)
		return (1);
	if (t == TRUNC)
		return (1);
	if (t == APPEND)
		return (1);
	if (t == HEREDOC)
		return (1);
	return (0);
}

static void	handle_redirection(t_token **tok, t_command *curr)
{
	if (!(*tok)->next || (*tok)->next->type != WORD)
	{
		printf("minishell: syntax error near unexpected token");
		return ;
	}
	add_redir(curr, (*tok)->type, (*tok)->next->token);
	*tok = (*tok)->next;
}

static void	handle_token(t_token **tok, t_command **curr)
{
	if ((*tok)->type == WORD)
		add_arg(*curr, (*tok)->token);
	else if (is_redirection((*tok)->type))
		handle_redirection(tok, *curr);
	else if ((*tok)->type == PIPE)
	{
		(*curr)->next = new_cmd();
		*curr = (*curr)->next;
	}
}

t_command	*parse_tokens(t_token *tok)
{
	t_command	*head;
	t_command	*curr;

	head = new_cmd();
	curr = head;
	while (tok)
	{
		handle_token(&tok, &curr);
		tok = tok->next;
	}
	return (head);
}
