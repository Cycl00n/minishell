/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 15:29:19 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/12 13:42:49 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_new_env_var(char *name, char *value, t_env *next)
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

	if (!env || !name || !name[0] || !value)
		return (1);
	curr = *env;
	prev = NULL;
	while (curr)
	{
//									ft_printf("loop setenv\n");
		if (!ft_strcmp(name, curr->name))
		{
	///										ft_printf("setenv cond ok\n");
			free(curr->value);
			curr->value = ft_strdup(value);
			return (0);
		}
		prev = curr;
		curr = curr->next;
	}
//									ft_printf("call new_env_var\n");
	curr = ft_new_env_var(name, value, NULL);
	if (!curr)
		return (1);
	if (prev)
		prev->next = curr;
	else
		*env = curr;
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
	value = ft_get_parent_shlvl();
	ft_set_env("SHLVL", value, env);
	free(value);
	value = getenv("PATH");
	if (!value)
		value = "/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin";
	ft_set_env("PATH", value, env);
	value = getenv("HOME");
	if (!value)
		value = "/home";
	ft_set_env("HOME", value, env);
	return (env);
}