/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 13:10:38 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/25 13:13:02 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
