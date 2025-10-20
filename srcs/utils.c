/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:56:43 by clnicola          #+#    #+#             */
/*   Updated: 2025/10/20 12:55:49 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tabs(char **args)
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

char	*get_path(char **env)
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

char	*get_cmd(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;
	char	*full_path;

	i = 0;
	if (!cmd || !*cmd)
		exit(1);
	path = ft_split(get_path(env), ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			free_tabs(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_tabs(path);
	return (NULL);
}

void	handle_cmd_errors(char **args, char *path)
{
	ft_putstr_fd("command not found: ", 2);
	ft_putstr_fd(args[0], 2);
	ft_putchar_fd('\n', 2);
	free(path);
	free_tabs(args);
	return ;
}