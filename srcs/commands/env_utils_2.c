/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 15:03:37 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/12 13:13:05 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	ft_copy_env_tail(t_env **new, t_env **old)
{
	t_env	*curr_n;
	t_env	*curr_o;

	curr_n = *new;
	curr_o = *old;

	while (curr_o->next)
	{
		curr_o = curr_o->next;
		curr_n->next = ft_new_env_var(curr_o->name, curr_o->value, NULL);
		if (!curr_n->next)
			return (-1);
		curr_n = curr_n->next;
	}
	return (0);
}

t_env	**ft_copy_env(t_env **env)
{
	t_env	**new;
	t_env	*browser;

	new = malloc(sizeof(t_env *));
	if (!env || !new)
		return NULL;
	browser = *env;
	if (!browser)
	{
		*new = NULL;
		return (new);
	}
	*new = ft_new_env_var(browser->name, browser->value, NULL);
	if (!*new)
	{
		ft_free_env(new);
		return (NULL);
	}
	if (ft_copy_env_tail(new, env))
	{
		ft_free_env(new);
		return (NULL);
	}
	return (new);
}

void	ft_swap_env(t_env **env, t_env *to_swap)
{
	t_env	*curr;
	t_env	*prev;

	curr = *env;
	prev = NULL;
	while (curr && curr != to_swap)
	{
		prev = curr;
		curr = curr->next;
	}
	if (!curr || !curr->next)
		return ;
	if (!prev)
	{
		*env = curr->next;
		curr->next = curr->next->next;
		(*env)->next = curr;
		return ;
	}
	prev->next = curr->next;
	curr->next = curr->next->next;
	prev->next->next = curr;
	return ;
}

void	ft_free_env(t_env **env)
{
	t_env	*prev;
	t_env	*curr;

	if (*env)
	{
		curr = *env;
		while (curr)
		{
			prev = curr;
			curr = curr->next;
			if (prev->name)
				free(prev->name);
			if (prev->value)
				free(prev->value);
			free(prev);
		}
	}
	free(env);
}
