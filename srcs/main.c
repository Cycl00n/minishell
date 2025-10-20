/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:26:49 by clnicola          #+#    #+#             */
/*   Updated: 2025/10/20 12:40:09 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	exec(char *cmd, char **env)
{
	char	*path;
	char	**args;
	pid_t	pid;
	int		status;

	if (cmd == NULL)
		return ;
	args = ft_split(cmd, ' ');
	if (!args[0])
	{
		free_tabs(args);
		return ;
	}
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
	{
		if (execve(path, args, env) == -1)
			handle_cmd_errors(args, path);
		exit(1);
	}
	waitpid(pid, &status, 0);
}

int	main(int ac, char **av, char **env)
{
	char	*readl;
	char	*pwd;

	ac = 0;
	av = NULL;
	while (1)
	{
		pwd = getcwd(NULL, 0);
		printf("%s", pwd);
		readl = readline("$ ");
		if (!ft_strncmp(readl, "exit", 5))
			exit(1);
		exec(readl, env);
		add_history(readl);
	}
	free(readl);
	return (0);
}
