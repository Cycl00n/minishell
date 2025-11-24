/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 14:19:02 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/24 12:29:58 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	print_args(t_command *cmd)
{
	int	i;

	printf("Command: ");
	i = 0;
	while (cmd->args && cmd->args[i])
	{
		printf("[%s] ", cmd->args[i]);
		i++;
	}
	printf("\n");
}

static void	print_redirects(t_redir *redir)
{
	while (redir)
	{
		printf("  Redirect: type=%d, file=[%s]\n", redir->type, redir->file);
		redir = redir->next;
	}
}

static void	ft_display_commands(t_command *cmd)
{
	while (cmd)
	{
		print_args(cmd);
		if (cmd->redirs)
			print_redirects(cmd->redirs);
		cmd = cmd->next;
	}
}

t_token	*ft_word_to_token(char *input)
{
	t_token	*head;
	t_token	*new;
	int		i;

	head = NULL;
	i = 0;
	while (input[i])
	{
		if (ft_is_space(input[i]))
		{
			i++;
			continue ;
		}
		new = ft_make_token(input, &i);
		ft_add_back_token(&head, new);
	}
	return (head);
}

void	ft_parsing(t_data *data, char *input)
{
	data->token = ft_word_to_token(input);
	ft_assign_token_type(data);
	data->cmd = ft_tokens_to_commands(data->token);
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
		ft_parsing(data, data->input);
		add_history(data->input);
		tmp = data->token;
		while (tmp)
		{
			printf("[%d] %s\n", tmp->type, tmp->token);
			tmp = tmp->next;
		}
		ft_display_commands(data->cmd);
	}
	free(data);
	return (0);
}
