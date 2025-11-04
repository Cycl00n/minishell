/* ************************************************************************* */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:08:58 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/04 14:55:47 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	word_to_token(t_data *data, char *input)
{
	int		i;
	char	**tokens;
	t_token	*new;
	t_token	*last;

	tokens = ft_split(input, ' ');
	data->token = NULL;
	i = -1;
	while (tokens[++i])
	{
		new = malloc(sizeof(t_token));
		new->token = ft_strdup(tokens[i]);
		new->next = NULL;
		if (!data->token)
			data->token = new;
		else
		{
			last = data->token;
			while (last->next)
				last = last->next;
			last->next = new;
		}
	}
}

void	assign_token_type(t_data *data)
{
	t_token	*tmp;

	tmp = data->token;
	while (tmp)
	{
		if (ft_strcmp(tmp->token, "|") == 0)
			tmp->type = PIPE;
		else if (ft_strcmp(tmp->token, "<<") == 0)
			tmp->type = HEREDOC;
		else if (ft_strcmp(tmp->token, ">>") == 0)
			tmp->type = APPEND;
		else if (ft_strcmp(tmp->token, "<") == 0)
			tmp->type = INPUT;
		else if (ft_strcmp(tmp->token, ">") == 0)
			tmp->type = TRUNC;
		else if (tmp->token[0] == '$' && tmp->token[1] != '\0')
			tmp->type = VAR;
		else
			tmp->type = WORD;
		tmp = tmp->next;
	}
}

void	parsing(t_data *data, char *input)
{
	word_to_token(data, input);
	assign_token_type(data);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	t_token	*tmp;

	(void)ac;
	(void)av;
	(void)env;
	data = malloc(sizeof(t_data));
	while (1)
	{
		data->input = readline("testenv$ ");
		if (!data->input)
			break ;
		parsing(data, data->input);
		tmp = data->token;
		while (tmp)
		{
			printf("[%d] %s\n", tmp->type, tmp->token);
			tmp = tmp->next;
		}
		free(data->input);
	}
	free(data->input);
	return (0);
}
