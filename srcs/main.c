/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:26:49 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/03 14:39:16 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	built_in_commands(t_data *data, char **env)
{
	char	**args;

	args = ft_split(data->input, ' ');
	if (!ft_strncmp(args[0], "echo", 4))
	{
		builtin_echo(data->input);
		return (1);
	}
	else if (!ft_strncmp(args[0], "exit", 4))
	{
		builtin_exit(data->input);
		return (1);
	}
	else if (!ft_strncmp(args[0], "env", 3))
	{
		builtin_env(data->input, env);
		return (1);
	}
	else
		return (0);
}

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
	char	*prompt;
	t_data	data;

	(void)ac;
	(void)av;
	while (1)
	{
		// data_init(&data, env);
		prompt = prompt_name();
		data.input = readline(prompt);
		parsing(&data);
		if (!built_in_commands(&data, env))
			exec(data.input, env);
		add_history(data.input);
	}
	free(data.input);
	return (0);
}
