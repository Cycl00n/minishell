/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:29:19 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/10 17:36:52 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_env	*ft_new_env_var(char *name, char *value, t_env *next)
{
	t_env	*curr;
	
	curr = malloc(sizeof(t_env));
	if (!curr)
		return (NULL);
	curr->name = ft_strdup(name);
	curr->value = ft_strdup(value);
	if (!curr->name || !curr->value)
	{
		if (curr->name)
			free(curr->name);
		if (curr->value)
			free(curr->value);
		free(curr);
		return(NULL);
	}
	curr->next = next;
	return (curr);
}

int	ft_set_env(char *name, char *value, t_env **env)
{
	t_env	*curr;
	t_env	*prev;

	if (!env || !name || !name[0])
		return (1);
													ft_putendl_fd("----set start OK", 1);
	curr = *env;
													ft_putendl_fd("----init curr OK", 1);
	while (curr)
	{
													ft_putendl_fd("----start loop cycle", 1);
		if (!ft_strcmp(name, curr->name))
		{
													ft_putendl_fd("----got equality", 1);
			free(curr->value);
			curr->value = ft_strdup(value);
													ft_putendl_fd("----replace value OK", 1);
			return (0);
		}
		prev = curr;
		curr = curr->next;
													ft_putendl_fd("----loopcycle OK", 1);
	}
													ft_putendl_fd("----endloop OK", 1);
	curr = ft_new_env_var(name, value, NULL);
														ft_putendl_fd("----create var OK", 1);
	if (!curr)
		return (1);
	if (prev)
		prev->next = curr;
	else
		*env = curr;
														ft_putendl_fd("----set end OK", 1);
	return (0);
}

int	ft_rm_env(char *name, t_env **env)
{
	t_env	*prev;
	t_env 	*curr;

	if (!name || !name[0] || !env)
		return (1);
	curr = *env;
	prev = NULL;
	while (curr)
	{
		if (!ft_strcmp(name, curr->name))
		{
			if (prev)
				prev->next = curr->next;
			else
				*env = curr->next;
			free(curr->name);
			free(curr->value);
			free(curr);
			break;	
		}
		prev = curr;
		curr = curr->next;
	}
	return (0);
}

static char	*ft_get_parent_shlvl(void)
{
	char	*tmp;
	int		lvl_number;
	char	*shlvl;

	tmp = getenv("SHLVL");
	if (!tmp)
		return (ft_strdup("1"));
	lvl_number = ft_atoi(tmp);
	lvl_number++;
	shlvl = ft_itoa(lvl_number);
	return (shlvl);
}

t_env **ft_initialize_env(void)
{
	char	*value;
	t_env	**env;

	env = calloc(sizeof(t_env *), 1);
	*env = ft_new_env_var("PWD", getcwd(NULL, 0), NULL);
													ft_putendl_fd("pwd OK", 1);
	value = ft_get_parent_shlvl();
													ft_putendl_fd("getshlvl OK", 1);
	ft_set_env("SHLVL", value, env);
													ft_putendl_fd("shlvl OK", 1);
	free(value);
	value = getenv("PATH");
													ft_putendl_fd("getpath OK", 1);
	if (!value)
		value = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	ft_set_env("PATH", value, env);
													ft_putendl_fd("path OK", 1);
	value = getenv("HOME");
													ft_putendl_fd("gethome OK", 1);
	if (!value)
		value = "/home";
	ft_set_env("HOME", value, env);
													ft_putendl_fd("home OK", 1);
	return (env);
}