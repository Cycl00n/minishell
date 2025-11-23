/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_path.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: clnicola <clnicola@student.42luxembourg    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/20 11:56:43 by clnicola          #+#    #+#             */
/*   Updated: 2025/11/23 20:17:20 by clnicola         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_cmd(char **env, char *cmd)
{
	int		i;
	char	**path;
	char	*temp;
	char	*full_path;

	i = 0;
	if (!cmd || !*cmd)
		exit(1);
	path = ft_split(ft_get_path(env), ':');
	while (path[i])
	{
		temp = ft_strjoin(path[i], "/");
		full_path = ft_strjoin(temp, cmd);
		free(temp);
		if (access(full_path, F_OK | X_OK) == 0)
		{
			ft_free_tabs(path);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	ft_free_tabs(path);
	return (NULL);
}
