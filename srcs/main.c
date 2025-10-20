/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:26:49 by clnicola          #+#    #+#             */
/*   Updated: 2025/10/20 20:13:47 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**parse_command(char *cmd)
{
	char	**args;

	if (cmd == NULL)
		return (NULL);
	args = ft_split(cmd, ' ');
	if (!args || !args[0])
	{
		if (args)
			free_tabs(args);
		return (NULL);
	}
	return (args);
}

static void	child(char *path, char **args, char **env)
{
	if (execve(path, args, env) == -1)
		handle_cmd_errors(args, path);
	exit(1);
}

void	exec(char *cmd, char **env)
{
	char	**args;
	char	*path;
	pid_t	pid;

	args = parse_command(cmd);
	if (!args)
		return ;
	path = get_cmd(env, args[0]);
	if (!path)
	{
		handle_cmd_errors(args, path);
		return ;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
		child(path, args, env);
	waitpid(pid, NULL, 0);
}

int	main(int ac, char **av, char **env)
{
	char	*readl;
	char	*prompt;

	(void)ac;
	(void)av;
	while (1)
	{
		prompt = prompt_name();
		readl = readline(prompt);
		if (!ft_strncmp(readl, "exit", 5))
		{
			free(readl);
			free(prompt);
			exit(1);
		}
		exec(readl, env);
		add_history(readl);
	}
	free(readl);
	return (0);
}
