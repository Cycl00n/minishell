/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_converter_args.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/23 18:26:35 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 22:00:00 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_build_args(t_token *token_list, int arg_count)
{
	char	**args;
	int		i;

	args = malloc(sizeof(char *) * (arg_count + 1));
	if (!args)
		return (NULL);
	i = 0;
	while (token_list && token_list->type != PIPE && i < arg_count)
	{
		if (token_list->type == WORD || token_list->type == VAR)
		{
			args[i] = ft_strdup(token_list->token);
			if (!args[i])
				return (NULL);
			i++;
		}
		token_list = token_list->next;
	}
	args[i] = NULL;
	return (args);
}

t_token	*ft_skip_to_next_pipe(t_token *token_list)
{
	while (token_list && token_list->type != PIPE)
		token_list = token_list->next;
	if (token_list && token_list->type == PIPE)
		token_list = token_list->next;
	return (token_list);
}
