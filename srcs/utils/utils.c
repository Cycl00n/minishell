/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:56:43 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 20:17:20 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_tabs(char **args)
{
	int	i;

	i = 0;
	if (args == NULL)
		return ;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

char	*ft_get_path(char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
			return (env[i] + 5);
		i++;
	}
	return (NULL);
}

char	*ft_prompt_name(void)
{
	char	*user;
	char	*tmp;
	char	*prompt;

	user = getenv("USER");
	tmp = ft_strjoin("\001\033[1;32m\002", user);
	prompt = ft_strjoin(tmp, "\033[0m\002$ ");
	free(tmp);
	return (prompt);
}

void	ft_handle_cmd_errors(char **args, char *path)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putchar_fd('\n', 2);
	free(path);
	ft_free_tabs(args);
}
