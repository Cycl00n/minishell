/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rlefort <rlefort@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:59:54 by rlefort           #+#    #+#             */
/*   Updated: 2025/11/10 18:57:36 by rlefort          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*build_var_line(t_env *var)
{
	char	*var_line;
	size_t	size;
	
	size = 11 + ft_strlen(var->name) + 2;
	if (var->value && var->value[0])
		size += 1 + ft_strlen(var->value);
	var_line = calloc(sizeof(char), size);
	ft_strlcat(var_line, "declare -x ", size);
	ft_strlcat(var_line, var->name, size);
	if (var->value && var->value[0])
	{
	ft_strlcat(var_line, "=", size);
	ft_strlcat(var_line, var->value, size);
	}
	ft_strlcat(var_line, "\n", size);
	return(var_line);
}

char	*ft_export_noargs(t_env **env)
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

void	ft_export(char **args, t_env **env)
{
	int		index;
	char	*eq_pos;
	char	*name;
	char	*value;

	if (!env || !args || !args[0])
		return ;
	index = 0;
	while (args[index])
	{
		if (args[index] && args[index][0])
		{
			name = args[index];
			value = NULL;
			eq_pos = ft_strchr(args[index], '=');
			if(eq_pos)
			{
			value = &eq_pos[1];
			name =ft_substr(args[index], 0, (size_t)(eq_pos - args[index]));
			}
			ft_set_env(name, value, env);
		}
		index++;
	}
}
