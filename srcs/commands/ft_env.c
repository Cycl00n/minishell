/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 14:03:33 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/11 15:34:59 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_var_line(t_env *var)
{
	char	*var_line;
	size_t	size;
	
	size = ft_strlen(var->name) + 2;
	if (var->value && var->value[0])
		size += 1 + ft_strlen(var->value);
	var_line = calloc(sizeof(char), size);
	ft_strlcat(var_line, var->name, size);
	if (var->value && var->value[0])
	{
		ft_strlcat(var_line, "=", size);
		ft_strlcat(var_line, var->value, size);
	}
	ft_strlcat(var_line, "\n", size);
	return(var_line);
}

char	*ft_env(t_env **env)
{
	char	*env_vars;
	char	*var_line;
	char	*tmp;
	t_env	*curr;

	if (!env)
		return (NULL);
	curr = *env;
	env_vars = calloc(1,1);
	while (curr)
	{
		if (curr->name && curr->name[0])
		{
			var_line = build_var_line(curr);
			tmp = ft_strjoin(env_vars, var_line);
			free(env_vars);
			free(var_line);
			if (!tmp)
				return (NULL);
			env_vars = tmp;
		}
		curr = curr->next;
	}
	return (env_vars);
}
